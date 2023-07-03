# Yolov5 Segmentation with NCNN

![cat.gif](./output/cat.gif)

---

## How to run

1. Put NCNN model (.bin and .param) to the "models" folder.
2. Put inference image to "input" folder
3. Put class names text file ( *.txt ) to "data" folder ( See the tree below )
4. Run yolov5-seg.exe in cmd ( assumed that the *.bin and*.param are both in models folder )

```
+---data
|       coco128.txt
|       
+---input
|       test.bmp
|       cat.jpg
|       cat.mp4
|
+---models
|       yolov5s-seg.ncnn.bin
|       yolov5s-seg.ncnn.param
|
+---output
|       cat.jpg
|       cat.mp4
|
+---Yolov5-seg
|       yoloncnn.exe
```  

```
Usage

yoloncnn [option] <value>

Options
    --model <ncnn model name>           = Explicitly specify the ncnn model name. Default yolov5s-seg.ncnn
    --data <class names txt file>       = Explicitly specify the class names txt file. Default coco128.txt
    --source <input source>             = Explicitly specify the input source. Default test.bmp
    --output <output folder>            = Explicitly specify the output folder. Default output
    --size <target size>                = Specify the target size. Default 640
    --conf <confident threshold>        = Specify the confident threshold. Default 0.25
    --nms <nms threshold>               = Specify the nms threshold. Default 0.45
    --max-obj <max objects detection>   = Specify the max objects detection. Default 100
    --dynamic                           = Dynamic inference flag. Default false
    --agnostic                          = Agnostic nms flag. Default false
    --contour                           = Draw contour instead of mask flag. Default false
    --save                              = Save output flag. Default false
    --save--text                        = Save output label to a text file flag. Default false
    --crop                              = Crop output flag. Default false
    --rotate                            = Rotate output flag. Default false
```

Note :

source can be :

- image path
- videos path
- 0 for webcam
- . for run all images in input folder

For example :

```
yoloncnn --input cat.jpg --model yolov5s-seg.ncnn --dynamic --save --agnostic
```

```
5 argument(s) passed
model     = ..\models\yolov5s-seg.ncnn.bin
param     = ..\models\yolov5s-seg.ncnn.param
input     = ..\input\cat.jpg
data      = ..\data\coco128.txt
size      = 640
conf      = 0.25
nms       = 0.45
maxObj    = 100
dynamic   = 1
contour   = 0
agnostic  = 1
crop      = 0
save      = 1
saveTxt   = 0
saveMask  = 0
------------------------------------------------
Inference time = 0.194 (seconds)
Objects count = 5
42 0.775778 496 459 719 568
15 0.551823 214 237 467 436
41 0.381012 2 170 104 538
42 0.318674 590 459 716 546
45 0.308080 92 444 581 615
Output saved at ..\output\cat.jpg
```

![cat.jpg](./output/cat.jpg)

---

## Wiki

- [Setup for windows, using visual studio 2022](https://github.com/canh25xp/Yolov5-segmentation-ncnn/wiki/How-to-build)
- [Convert pytorch to ncnn](https://github.com/canh25xp/Yolov5-segmentation-ncnn/wiki/Convert-pytorch-model-to-ncnn-model)

---

## MEME PLACE

Scientists : AI is going to take over the world.

Mean while AI :

![meme.jpg](./output/meme.jpg)
