//
// Created by alro on 18‏/4‏/2021.
//

#ifndef VALRAVN_STORAGE_MANAGER_H
#define VALRAVN_STORAGE_MANAGER_H


class StorageManager {
public:
    size_t static get_file_size(string_view file_path){
        try {
            ifstream in_file(file_path.data(), ios::binary);
            in_file.seekg(0, ios::end);
            int file_size = in_file.tellg();
            cout<<"Size of the file is "<< file_size<<" bytes"<<endl;
            return file_size;
        }catch( exception & e){
            cout<<e.what()<<endl;
            return -1 ;
        }
    }
};


#endif //VALRAVN_STORAGE_MANAGER_H
