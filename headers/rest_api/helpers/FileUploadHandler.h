//
// Created by alro on 18‏/4‏/2021.
//

#ifndef VALRAVN_STORAGE_MANAGER_H
#define VALRAVN_STORAGE_MANAGER_H

#define DOWNLOAD_PATH "/home/alla/Videos/"

using oatpp::web::protocol::http::incoming::Request;
template <class T>
using DtoObject = oatpp::data::mapping::type::DTO::Object<T>;
#include "oatpp/core/Types.hpp"


class FileUploadHandler {

private:
    std::shared_ptr<multipart::PartList> multipart;
    std::shared_ptr<multipart::Part> file_part;
    string temp_path;
    string storage_path;
    string file_name;
    string resolution;
    string content_type;
    size_t size;
    shared_ptr<oatpp::data::stream::InputStream> inputStream;

    multipart::Reader init_oatpp_reader()
    {
        /* Create multipart reader. */
        multipart::Reader multipartReader(multipart.get());

        /* Configure to stream part with name "part1" to file */
        multipartReader.setPartReader("file", multipart::createFilePartReader(temp_path.c_str()));
        multipartReader.setPartReader("resolution", multipart::createInMemoryPartReader(256 /* max-data-size */));
        return multipartReader;
    }

    /**
     *
     * @return a path used to store a fully downloaded file
     */
    void init_storage_path()
    {
        std::time_t t = std::time(nullptr);
        this->storage_path = DOWNLOAD_PATH + to_string(t) + "-" + this->file_name;
    }

    /**
     *
     * init path for a temporary file used to download a file.
     */
    void init_temp_file_path()
    {
        std::time_t t = std::time(nullptr);
        this->temp_path = DOWNLOAD_PATH + to_string(t) + "temp";
    }

public:

    explicit FileUploadHandler(shared_ptr<Request> request)
    {
        this->multipart = std::make_shared<multipart::PartList>(request->getHeaders());
        init_temp_file_path();
        multipart::Reader multipartReader = init_oatpp_reader();
        request->transferBody(&multipartReader);
        this->file_part = this->multipart->getNamedPart("file");
        OATPP_ASSERT_HTTP(this->file_part, ImageController::Status::CODE_400, "file is non valid");
        this->inputStream  = this->file_part->getPayload()->openInputStream();
        this->resolution   = this->multipart->getNamedPart("resolution")->getPayload()->getInMemoryData();
        this->content_type = this->file_part->getHeaders().getAll().find("Content-Type")->second.std_str();
        this->file_name    = *file_part->getFilename();
        init_storage_path();
    }

    /**
     *
     * @return the size in bytes of the file.
     */
    void init_file_size(){
        try {
            ifstream in_file(this->storage_path, ios::binary);
            in_file.seekg(0, ios::end);
            this->size = in_file.tellg();
            cout<<"Size of the file is "<< this->size <<" bytes"<<endl;
        }catch( exception & e){
            cout<<e.what()<<endl;
            this->size = -1;
        }
    }

     void store()
     {
         string error_msg = "could not create the file with the name: " + file_name;
         if(rename(temp_path.c_str(), storage_path.c_str()) != 0)
         {
             throw error_msg;
         }
         init_file_size();
         if(size<=0)
         {
             throw error_msg;
         }
     }

    DtoObject<ImageDto> save_as_image()
    {
        unique_ptr<Image> image = MediaUploadDto::createImageFromDto(storage_path, content_type, resolution, size);
        image->save();
        return ImageDto::createDtoFromEntity(*image);
    }

    DtoObject<VideoDTO> save_as_video(time_t duration)
    {
        unique_ptr<Video> video = MediaUploadDto::createVideoFromDto(storage_path, content_type, resolution, size, duration);
        video->save();
        return VideoDTO::createDtoFromEntity(*video);
    }



     void remove()
     {
         std::remove(temp_path.c_str());
         cout<< "File located in: " << temp_path << " have been removed."<<endl;
     }


    [[nodiscard]] string_view get_storage_path() const {
        return storage_path;
    }

    [[nodiscard]] string_view get_content_type() const {
        return content_type;
    }


};


#endif //VALRAVN_STORAGE_MANAGER_H
