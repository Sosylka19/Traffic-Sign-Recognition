## Project struct


НАПИСАТЬ полный план как проходило обучение по дням
Чуваку нужно скачать qt, onnx, docker

дока к скачиванию инференса:https://github.com/ultralytics/ultralytics/blob/main/examples/YOLOv8-ONNXRuntime-CPP/README.md

```traffic_sign_detection/
├── data/
│   └── model/
│       ├── resnet34_gtsrb.onnx
│       └── labels/
│            └── classes_name.json
│
├── ml_core/
│   ├── dataloader.py                         
│   ├── model.py               
│   └── utils.py  
│    
├── qui/
│   ├──               
│   └──        
│    
├── db/5
│   ├──               
│   └──      
│
├── inference/
│   ├── CMakeLists.txt       
│   └── inference.cpp                 
│
├── notebooks/
│   └── notebook(eda & whole cnn).ipynb    
│
├── requirements.txt
└── README.md  

### Download OnnxRuntime