#ifndef RDK_UCLASSIFIERRESSAVER_CPP
#define RDK_UCLASSIFIERRESSAVER_CPP

#include <boost/filesystem.hpp>
#include "UClassifierResSaver.h"

namespace RDK {



// Методы
// --------------------------
// Конструкторы и деструкторы
// --------------------------
UClassifierResSaver::UClassifierResSaver(void):
    SaveDirectory("SaveDirectory", this),
    ImageName("ImageName",this),
    InputImage("InputImage",this),
    InputImages("InputImages",this),
    InputClasses("InputClasses",this),
    InputConfidences("InputConfidences", this),
    OverwriteSaveDirectory("OverwriteSaveDirectory",this),
    CalculateFlag("CalculateFlag",this),
    ObjectsName("ObjectsName",this)
{
    OverwriteSaveDirectory = false;
    CalculateFlag = false;
    (*ObjectsName).insert(pair<int, std::string>(-5,"mock"));
}

UClassifierResSaver::~UClassifierResSaver(void)
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
UClassifierResSaver* UClassifierResSaver::New(void)
{
 return new UClassifierResSaver;
}
// --------------------------


// --------------------------
// Скрытые методы управления счетом
// --------------------------
bool UClassifierResSaver::ACalculate(void)
{
    if(!InputConfidences.IsConnected() || !InputClasses.IsConnected())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Inputs: [InputConfidences] or [InputClasses] is not connected"));
        return true;
    }

    if(InputConfidences->IsEmpty() || InputClasses->IsEmpty())
    {
        LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Inputs: [InputConfidences] or [InputClasses] is empty"));
        return true;
    }


    if(InputImages.IsConnected() && InputImages->size()>0)
    {
        for(int i=0; i<InputImages->size(); i++)
        {
            ProcessedBmp = (*InputImages)[i];

            if(ProcessedBmp.GetData()==NULL)
            {
                LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImages["+sntoa(i)+"] is NULL"));
                continue;
            }

            int class_id = (*InputClasses)[i];

            MDMatrix<double> confidences;

            confidences.Assign(1, InputConfidences->GetCols(), 0.0);

            for(int k=0; k< InputConfidences->GetCols(); k++)
            {
                (confidences)(0, k) = (*InputConfidences)(i,k);
            }

            if(!SaveImage(ProcessedBmp, class_id, confidences))
            {
                LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Error while saving classification results"));
            }
        }
    }
    else
    {
        if(InputImage.IsConnected())
        {
            ProcessedBmp = (*InputImage);

            if(ProcessedBmp.GetData()==NULL)
            {
                LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("InputImage is NULL"));
                return true;
            }

            int class_id = (*InputClasses)[0];

            MDMatrix<double> confidences;

            confidences.Assign(1, InputConfidences->GetCols(), 0.0);

            for(int k=0; k< InputConfidences->GetCols(); k++)
            {
                (confidences)(0, k) = (*InputConfidences)(0,k);
            }

            if(!SaveImage(ProcessedBmp, class_id, confidences))
            {
                LogMessageEx(RDK_EX_WARNING, __FUNCTION__, std::string("Error while saving classification results. Function [SaveImage]"));
            }
        }
    }



    return true;
}

bool UClassifierResSaver::SaveImage(UBitmap& img, int class_id, MDMatrix<double>& confidences)
{
    std::string save_path = Environment->GetCurrentDataDir()+"Results/";

    //Создаем директорию Results в папке проекта
    if(RDK::CreateNewDirectory(save_path.c_str())!=0)
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UClassifierResSaver error: error while creating \"Results\" directory. Full path: " + save_path));
        return false;
    }

    if(SaveDirectory->empty())
    {
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UClassifierResSaver error: \"SaveDirectory\" parameter is empty"));
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
        LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UClassifierResSaver error: error while creating \"{SaveDirectory}\" directory. Full path: " + save_path));
        return false;
    }
    std::string images_path = save_path + "images/";

    // Если имя изобаржения не подключено, создается папка images, куда далее сохраняются изображения
    if(!ImageName.IsConnected())
    {
        if(RDK::CreateNewDirectory(images_path.c_str())!=0)
        {
            LogMessageEx(RDK_EX_WARNING,__FUNCTION__,std::string("UClassifierResSaver error: error while creating \"{SaveDirectory}/images\" directory. Full path: " + images_path));
            return false;
        }
    }

    static int ii=0;

    std::map<int,std::string>::iterator class_name = (*ObjectsName).find(class_id);
    std::string cl_name;
    if(class_name != (*ObjectsName).end())
    {
        cl_name = class_name->second;
    }
    else
    {
        cl_name = RDK::sntoa(class_id);
    }

    std::stringstream img_path;
    if(!ImageName.IsConnected())
    {
        img_path << images_path;

        RDK::UBitmap TempBitmap;
        img.ConvertTo(TempBitmap);
        TempBitmap.SwapRGBChannels();
        //TempBitmap.ReflectionX();

        jpge::params param;
        param.m_quality=100;

        img_path << ii;

        img_path << ".jpg";
        //   jpge::jpeg_encoder jpeg_e;
        jpge::compress_image_to_jpeg_file(img_path.str().c_str(), TempBitmap.GetWidth(), TempBitmap.GetHeight(), 3,
                                       TempBitmap.GetData(),param);

        ii++;
    }
    else
    {
        img_path << *ImageName;
    }

    // Добавление разметки в файл разметки
    std::string annotation_path = save_path + "annotations.txt";
    std::ofstream annotation_file;
    annotation_file.open(annotation_path.c_str(), std::ios::app);
    annotation_file << img_path.str() << " " << cl_name << " " << confidences(0,class_id) << "\n";
    annotation_file.close();

    return true;

}

}
#endif



