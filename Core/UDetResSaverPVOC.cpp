#ifndef RDK_UDETRESSAVERPVOC_CPP
#define RDK_UDETRESSAVERPVOC_CPP

#include <boost/filesystem.hpp>
#include "UDetResSaverPVOC.h"

namespace RDK {



// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UDetResSaverPVOC::UDetResSaverPVOC(void) :
    InputImage("InputImage",this),
    ImageName("ImageName",this),
    InputObjects("InputObjects",this),
    SaveDirectory("SaveDirectory",this),
    OverwriteSaveDirectory("OverwriteSaveDirectory",this),
    CalculateFlag("CalculateFlag",this),
    ObjectsName("ObjectsName",this)
{
    OverwriteSaveDirectory = false;
    CalculateFlag = false;
    (*ObjectsName).insert(pair<int, std::string>(-5,"mock"));
}

UDetResSaverPVOC::~UDetResSaverPVOC(void)
{

}
// --------------------------


// ---------------------
// Методы управления параметрами
// ---------------------
// ---------------------

// ---------------------
// Методы управления переменными состояния
// ---------------------
// ---------------------

// --------------------------
// Системные методы управления объектом
// --------------------------
// Выделяет память для новой чистой копии объекта этого класса
UDetResSaverPVOC* UDetResSaverPVOC::New(void)
{
 return new UDetResSaverPVOC;
}
// --------------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------
bool UDetResSaverPVOC::ACalculate(void)
{
    if(!InputObjects.IsConnected())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Inputs: [InputObjects] is not connected"));
        return true;
    }

    if(InputObjects->IsEmpty())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Inputs: [InputObjects] is empty"));
        return true;
    }

    if(!InputImage.IsConnected())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Inputs: [InputObjects] is empty"));
    }

    if(!SaveImage())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Error while saving detection results. Function [SaveImage]"));
    }

    return true;
}

bool UDetResSaverPVOC::SaveImage()
{
    std::string save_path = Environment->GetCurrentDataDir()+"Results/";

    //Создаем директорию Results в папке проекта
    if(RDK::CreateNewDirectory(save_path.c_str())!=0)
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UDetResSaverPVOC error: error while creating \"Results\" directory. Full path: " + save_path));
        return false;
    }

    if(SaveDirectory->empty())
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UDetResSaverPVOC error: \"SaveDirectory\" parameter is empty"));
        return false;
    }


    std::string save_directory = SaveDirectory;
    // Если новый запуск (новый компонент) и директория уже существует ЛИБО название папки изменилось извне и директория уже существует
    if( (!CalculateFlag && boost::filesystem::exists(save_path+SaveDirectory->c_str())) || ( (OldSaveDirectory != *SaveDirectory) && boost::filesystem::exists(save_path+SaveDirectory->c_str())))
    {
        // Если перезаписываем
        if(OverwriteSaveDirectory)
        {
            // Удаляем директорию
            std::string temp = save_path + SaveDirectory->c_str();
            std::vector<std::string> folders;
            RDK::FindFilesList(temp.c_str(),"*",false,folders);

            // Удаление внутренних папок
            for(int k = 0; k < folders.size(); k++)
            {
                std::string inner_folder = temp + "/" + folders.at(k).c_str();
                RDK::DeleteDirectory(inner_folder.c_str());
            }

            RDK::DeleteDirectory(temp.c_str());
        }
        else
        {
            // Генерация нового имени для директории с некоторым индексом
            int folder_id = 0;

            while(boost::filesystem::exists(save_path + SaveDirectory->c_str()))
            {
                folder_id ++;
                SaveDirectory = save_directory + "_" + RDK::sntoa(folder_id);
                // TODO возможно ли ситуация когда названий папок не останется?
                // то есть все папки включая INT_MAX и INT_MIN будут заняты. делать break и error?
            }
        }
    }

    CalculateFlag = true;
    OldSaveDirectory = SaveDirectory;
    // Создание директории для сохранения
    save_path = save_path + SaveDirectory->c_str() + "/";

    //Создаем директорию {SaveDirectory} в папке Results
    if(RDK::CreateNewDirectory(save_path.c_str())!=0)
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UDetResSaverPVOC error: error while creating \"{SaveDirectory}\" directory. Full path: " + save_path));
        return false;
    }

    std::string images_path = save_path;
    std::string annotation_path = save_path;

    images_path = images_path + "images/";
    //Создаем директорию {images} в папке {SaveDirectory}
    if(RDK::CreateNewDirectory(images_path.c_str())!=0)
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UDetResSaverPVOC error: error while creating \"{images}\" directory. Full path: " + images_path));
        return false;
    }

    annotation_path = annotation_path + "annotations/";
    //Создаем директорию {annotations} в папке {SaveDirectory}
    if(RDK::CreateNewDirectory(annotation_path.c_str())!=0)
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UDetResSaverPVOC error: error while creating \"{annotations}\" directory. Full path: " + annotation_path));
        return false;
    }


    ProcessedBmp = (*InputImage);

    if(ProcessedBmp.GetData()==NULL)
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImage is NULL"));
        return true;
    }

    // Имя файла изображения и разметки
    static int name = 0;

    string img_name;

    RDK::UBitmap TempBitmap;
    ProcessedBmp.ConvertTo(TempBitmap);
    TempBitmap.SwapRGBChannels();

    if(ImageName.IsConnected() && !ImageName->empty())
    {
        std::size_t last_slash_place = (*ImageName).find_last_of("/");

        if(last_slash_place  == std::string::npos)
        {
            img_name = (*ImageName);
        }
        else
        {
            img_name =  (*ImageName).substr(last_slash_place+1);
        }
    }
    else
    {
         img_name = RDK::sntoa(name) + ".jpg";
         // Сохранение изображения в папке images

         jpge::params param;
         param.m_quality=100;

         stringstream img_path;
         img_path << images_path;
         img_path << img_name;

         //   jpge::jpeg_encoder jpeg_e;
         jpge::compress_image_to_jpeg_file(img_path.str().c_str(), TempBitmap.GetWidth(), TempBitmap.GetHeight(), 3,
                                        TempBitmap.GetData(),param);
    }


    // Сохранение XML файла разметки
    // Описание класса (отсюда формируются свойства)
    USerStorageXML AnnotationXML;

    AnnotationXML.Create("annotation");

    AnnotationXML.AddNode("folder");
    AnnotationXML.SetNodeText("images");
    AnnotationXML.SelectUp();

    AnnotationXML.AddNode("filename");
    AnnotationXML.SetNodeText(img_name);
    AnnotationXML.SelectUp();

    AnnotationXML.AddNode("path");

    if(ImageName.IsConnected() && !ImageName->empty())
    {
        AnnotationXML.SetNodeText(*ImageName);
    }
    else
    {
        AnnotationXML.SetNodeText("../images/"+ img_name);
    }

    AnnotationXML.SelectUp();

    AnnotationXML.AddNode("source");
    AnnotationXML.AddNode("database");
    // TODO что тут?
    AnnotationXML.SetNodeText("Unknown");
    AnnotationXML.SelectUp();
    AnnotationXML.SelectUp();

    // Размер изображения
    AnnotationXML.AddNode("size");

    AnnotationXML.AddNode("width");
    AnnotationXML.SetNodeText(RDK::sntoa(TempBitmap.GetWidth()));
    AnnotationXML.SelectUp();

    AnnotationXML.AddNode("height");
    AnnotationXML.SetNodeText(RDK::sntoa(TempBitmap.GetHeight()));
    AnnotationXML.SelectUp();

    AnnotationXML.AddNode("depth");
    AnnotationXML.SetNodeText(RDK::sntoa(TempBitmap.GetPixelByteLength()));
    AnnotationXML.SelectUp();

    AnnotationXML.SelectUp();


    AnnotationXML.AddNode("segmented");
    AnnotationXML.SetNodeText("0");
    AnnotationXML.SelectUp();



    for(int i = 0; i < InputObjects->GetRows(); i++)
    {
        AnnotationXML.AddNode("object");
        AnnotationXML.AddNode("name");

        std::map<int,std::string>::iterator class_name = (*ObjectsName).find(int((*InputObjects)(i,5)));

        if(class_name != (*ObjectsName).end())
        {
            AnnotationXML.SetNodeText(class_name->second); // имя класса
        }
        else
        {
            AnnotationXML.SetNodeText(RDK::sntoa((*InputObjects)(i,5))); // номер класса
        }

        AnnotationXML.SelectUp();

        AnnotationXML.AddNode("pose");
        AnnotationXML.SetNodeText("Unspecified");
        AnnotationXML.SelectUp();

        AnnotationXML.AddNode("truncated");
        AnnotationXML.SetNodeText("0");
        AnnotationXML.SelectUp();

        AnnotationXML.AddNode("difficult");
        AnnotationXML.SetNodeText("0");
        AnnotationXML.SelectUp();

        // Рамка
        AnnotationXML.AddNode("bndbox");

        AnnotationXML.AddNode("xmin");
        AnnotationXML.SetNodeText(RDK::sntoa((*InputObjects)(i,0)));
        AnnotationXML.SelectUp();

        AnnotationXML.AddNode("ymin");
        AnnotationXML.SetNodeText(RDK::sntoa((*InputObjects)(i,1)));
        AnnotationXML.SelectUp();

        AnnotationXML.AddNode("xmax");
        AnnotationXML.SetNodeText(RDK::sntoa((*InputObjects)(i,2)));
        AnnotationXML.SelectUp();

        AnnotationXML.AddNode("ymax");
        AnnotationXML.SetNodeText(RDK::sntoa((*InputObjects)(i,3)));
        AnnotationXML.SelectUp();

        AnnotationXML.SelectUp();
        AnnotationXML.SelectUp();
    }

    std::size_t dot_place = img_name.find_last_of(".");
    img_name = img_name.substr(0,dot_place);

    std::string file_name = annotation_path + RDK::sntoa(name) + ".xml";
    AnnotationXML.SaveToFile(file_name);

    name++;
    return true;
}

}
#endif



