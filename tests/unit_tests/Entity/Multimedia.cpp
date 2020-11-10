//
// Created by alro on 18‏/10‏/2020.
//

#include "gtest/gtest.h"

#include "Entity/Multimedia.h"

TEST(Multimedia, testGetPath){
    Multimedia m(1, "path", 50, "type");
    string new_path = "ejdid";
    new_path += m.getPath();
    Multimedia m_updated(m.getId(), new_path, m.getSize(), m.getMimeType());
    cout<<m_updated.getPath();
}

TEST(Multimedia, testGetPathShort){
    Multimedia m(1, "path", 50, "type");
    ASSERT_EQ(m.getPath(),"path");
    ASSERT_EQ(m.getMimeType(),"type");
}
