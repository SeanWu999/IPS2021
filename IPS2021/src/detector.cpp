#include "detector.h"

Detector::Detector(vector<queue<Mat>> *inputQueuePtrList, vector<queue<string>> *inputResultQueueList):imgPtrList(inputQueuePtrList), resultQueueList(inputResultQueueList){

}

Detector::~Detector(){

}

void Detector::initRockontrolModel(string model_path){
    cout << "init PET Model ..." << endl;
    //读取so库
    /*void *lib_dl = dlopen(model_path.c_str(),RTLD_NOW || RTLD_DEEPBIND);
    if(lib_dl == NULL){
        const char *dlmsg = dlerror();
        printf("dlopen failed!%s\n",dlmsg);
    }


    //模型so库初始化
    model_init_ptr = (ModelInitHandle)dlsym(lib_dl,"ModelInit");
    //释放模型so库资源,0-失败，1-成功
    model_deinit_ptr = (ModelDeinitHandle)dlsym(lib_dl,"ModelDeinit");
    //图像进行模型推理
    model_process_ptr = (ModelProcessHandle)dlsym(lib_dl,"ModelProcess");
    //获取模型描述参数
    model_desc_ptr = (GetModelDescHandle)dlsym(lib_dl,"GetModelDesc");

    if(model_init_ptr == NULL){
        printf("[ERROR] Get ModelInit Hanlde Error!\n");
        return;
    }

    handle = model_init_ptr();
    char model_desc_char[1024] = {0};
    model_desc_ptr(handle,model_desc_char);
    std::string model_desc_string(model_desc_char);

    rapidjson::Document json_value;
    json_value.Parse(model_desc_string.c_str());
    net_type = json_value["net_type"].GetString();
    model_type = json_value["model_type"].GetString();
    batch_size = json_value["batch_size"].GetInt();
    if(batch_size != 1)
    {
        printf("[ERROR]TENSORRT PLATFORM ONLY SUPPORT BATCH=1!\n");
        return;
    }

    img_format = json_value["data_format"].GetString();
    float etem_scale = 0;

    if(0 == strcmp(img_format.c_str(),"BGR") || 0 == strcmp(img_format.c_str(),"BGRB"))
    {
        etem_scale = 3.0;
    }
    else if(0 == strcmp(img_format.c_str(),"RGB") || 0 == strcmp(img_format.c_str(),"RGBP"))
    {
        etem_scale = 3.0;
    }
    else
    {
        etem_scale = 1.5;
    }

    input_channel = json_value["model_inputs"][0]["shape"][0].GetInt();
    input_height = json_value["model_inputs"][0]["shape"][1].GetInt();
    input_width = json_value["model_inputs"][0]["shape"][2].GetInt();
    buffer_size = input_width * input_height * etem_scale;

    input_buffer = (unsigned char*)malloc(buffer_size *sizeof(char));
    pet_threshold = 0.5;
    */

}

void Detector::runInference(){
    int number = 0;
    while(isRunning){
        for(size_t i=0; i<imgPtrList->size(); i++){
            if(imgPtrList->at(i).size() > 0){
                Mat image = imgPtrList->at(i).front();
                imgPtrList->at(i).pop();
                /*
                   ***************************
                   *** inference code here ***
                   ***************************
                */
                cout << "Queue " << i << " inferencing ...... left: " << imgPtrList->at(i).size() << endl;
                number ++;
                //imwrite("./save/" + to_string(number) + ".jpg",image);
                string label = "";
            }
        }

        usleep(100 * 1000);
    }

    // release all left images
    for(size_t i=0; i<imgPtrList->size(); i++){
        if(imgPtrList->at(i).size() > 0){
            imgPtrList->at(i).pop();
        }
    }

}

void Detector::start(){
    cout << "start inference work ......" << endl;
    isRunning = true;
    thread t(&Detector::runInference,this);
    t.detach();
}

void Detector::stop(){
    cout << "stop inference work ......" << endl;
    isRunning = false;
}

void Detector::release(){

}
