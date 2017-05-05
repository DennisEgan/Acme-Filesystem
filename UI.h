//
// Created by dennis on 5/5/17.
//

#ifndef MOBILE_FILESYSTEM_UI_H
#define MOBILE_FILESYSTEM_UI_H

#include "FileSystem.h"

class UI{
    public:
        UI();
        ~UI();

        // Class methods
        bool create(string);
        bool edit(string);
        bool type(string);
        void dir();
        bool deleteFile(string);
        void run();

    private:
        FileSystem FS;
};

#endif //MOBILE_FILESYSTEM_UI_H
