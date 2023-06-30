#include "yolo.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
    InputParser argument(argc, argv);

    //set folder path
    std::string inputFolder     = "..\\input";
    std::string outputFolder    = "..\\output";
    std::string modelFolder     = "..\\models";
    std::string dataFolder      = "..\\data";

    //set default argument
    std::string model     = argument.setDefaultArgument("--model", "yolov5s-seg.ncnn");
    std::string data      = argument.setDefaultArgument("--data", "coco128.txt");
    std::string input     = argument.setDefaultArgument("--source", "test.bmp");
    std::string output	  = argument.setDefaultArgument("--output", outputFolder);
    int size              = argument.setDefaultArgument("--size", 640);
    float conf            = argument.setDefaultArgument("--conf", 0.25f);
    float nms             = argument.setDefaultArgument("--nms", 0.45f);
    int maxObj            = argument.setDefaultArgument("--max-obj", 100);
    bool dynamic          = argument.cmdOptionExists("--dynamic");
    bool contour            = argument.cmdOptionExists("--contour");
    bool agnostic         = argument.cmdOptionExists("--agnostic");
    bool crop             = argument.cmdOptionExists("--crop");
    bool save             = argument.cmdOptionExists("--save");
    bool saveTxt          = argument.cmdOptionExists("--save-txt");
    bool saveMask		  = argument.cmdOptionExists("--save-mask");
    bool rotate			  = argument.cmdOptionExists("--rotate");

    std::cout << argument.argNum() << " argument(s) passed";

    std::filesystem::path inputPath  = inputFolder  +   "\\" + input;
    std::filesystem::path dataPath   = dataFolder   +   "\\" + data;
    std::filesystem::path bin        = modelFolder  +   "\\" + model + ".bin";
    std::filesystem::path param      = modelFolder  +   "\\" + model + ".param";
    std::filesystem::path outputPath = output;

    std::cout   << "\nmodel     = " << bin.string()
                << "\nparam     = " << param.string()
                << "\ninput     = " << inputPath.string()
                << "\ndata      = " << dataPath.string()
                << "\nsize      = " << size
                << "\nconf      = " << conf
                << "\nnms       = " << nms
                << "\nmaxObj    = " << maxObj
                << "\ndynamic   = " << dynamic
                << "\ncontour   = " << contour
                << "\nagnostic  = " << agnostic
                << "\ncrop      = " << crop
                << "\nsave      = " << save
                << "\nsaveTxt   = " << saveTxt
                << "\nsaveMask  = " << saveMask
                << "\nrotate    = " << rotate
                << "\n------------------------------------------------" <<std::endl;

    Yolo Yolov5;

    // load param and bin, assuming param and bin file has the same name
    if (Yolov5.load(bin, param)) {
        return -1;
    }
    Yolov5.get_class_names(dataPath);

    Yolov5.dynamic        = dynamic;
    Yolov5.save           = save;
    Yolov5.target_size    = size;
    Yolov5.prob_threshold = conf;
    Yolov5.nms_threshold  = nms;
    Yolov5.drawContour    = contour;
    Yolov5.agnostic       = agnostic;
    Yolov5.max_object     = maxObj;
    Yolov5.saveTxt		  = saveTxt;
    Yolov5.crop			  = crop;
    Yolov5.saveMask		  = saveMask;
    Yolov5.rotate		  = rotate;

    if (input == ".") {
        std::cout << "Auto running on all images in the input folder" ;
        int count = 0;
        clock_t tStart = clock();
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(inputFolder)) {
			std::string path = entry.path().string();
            std::cout << "\n------------------------------------------------" << std::endl;
            std::cout << path << std::endl;
            if (isImage(path)) {
                count++;
			    Yolov5.image(entry.path(), outputPath, true);
			}
            else {
                std::cout << "skipping non image file";
            }
		}
        auto total = (double)(clock() - tStart) / CLOCKS_PER_SEC;
        double average = total / count;
		std::cout << "\n------------------------------------------------" << std::endl;
		std::cout << count << " images processed" << std::endl;
        std::cout << "Total time taken: " << total << " seconds" << std::endl;
        std::cout << "Average time taken: " << average << " seconds" << std::endl;
		return EXIT_SUCCESS;
    }

    if (isImage(inputPath)) {
        Yolov5.image(inputPath, outputPath);
        return EXIT_SUCCESS;
    }
    if (input == "0" or isVideo(inputPath)) {
        Yolov5.video(inputPath.string());
        return EXIT_SUCCESS;
    }

    std::cout << "input type not supported";
    return EXIT_FAILURE;
}
