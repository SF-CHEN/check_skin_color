//参考下面博客中的文章以及代码编写
//http://www.cnblogs.com/Imageshop/p/3264238.html
//2015/11/25
//by jiang pei
//
#include <opencv.hpp>

using namespace cv;
using namespace std;

const string path = "xiaofeng2.jpg";

int main()
{
	Mat source = imread(path);
	Mat skin_image;
	skin_image=Mat::zeros(source.size(), CV_8U);
	

	int width = source.cols;
	int height = source.rows;
	int blue, green, red, Sum,T1,T2,Lower,Upper;

	for (int h = 0; h < height;++h)
	{
		uchar* data = source.ptr(h);
		uchar* skin_data = skin_image.ptr(h);
		for (int w = 0; w < width;++w)
		{
			blue = data[3 * w];
			green = data[3 * w + 1];
			red = data[3 * w + 2];
			if (red-green>=45)            //符合条件R4
			{
				if (green > blue)         //符合条件R3
				{
					Sum = blue + green + red;
					T1 = 156 * red - 52 * Sum;
					T2 = 156 * green - 52 * Sum;
					if (T1*T1+T2*T2>=(Sum*Sum)>>4)  //符合条件R2
					{
						T1 = 10000 * green * Sum;
						Lower = -7760 * red*red + 5610 * red*Sum + 1766 * Sum*Sum;
						if (T1>Lower)                   //符合条件R11
						{
							Upper = -13767 * red*red + 10743 * red*Sum + 1452 * Sum*Sum;
							if (T1<Upper)             //符合条件R12
							{
								skin_data[w] = 255;
							}
						}

					}
				}
			}
			
		}
	}
	string path_out = path + "_out.jpg";
	imwrite(path_out, skin_image);
}