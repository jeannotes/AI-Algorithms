#include <iostream>
#include <stdio.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <dirent.h>
#include <iterator>

using namespace std;

int main(int argc, char** argv)
{
  pcl::PointCloud<pcl::PointXYZI> cloud;

  DIR* dir;
  dirent* pdir;
  int track =1;
  char filename[300];
  
  dir = opendir("/home/ramrao/velodyne/fresh/");
  while(pdir = readdir(dir)) {

    int number_of_lines = 0;
    cout << pdir->d_name << endl;
    int dot = strcmp(pdir->d_name, ".");
    int dot_dot = strcmp(pdir->d_name, "..");
    if(dot == 0 || dot_dot == 0){
      continue;   
    }
    std::strcpy(filename, "/home/ramrao/velodyne/fresh/");
    std::strcat(filename, pdir->d_name);
    ifstream infile(filename);
    ifstream fle(filename);

    std::string line;  
    while(std::getline(fle, line))
      ++number_of_lines;


      // ifstream infile("/home/ramrao/velodyne/test.txt");

    cout << "Number of lines " << number_of_lines << endl;
    cloud.width = number_of_lines;
    cloud.height = 1;
    cloud.points.resize (cloud.width * cloud.height);
    std::cout << cloud.points.size() << std::endl;

    float name;
    float var1;
    float var2;
    float var3;
    float var4;
    size_t i=0;
    cout << "Here" << endl;
    while(infile >> name >> var1 >> var2 >> var3) {
     cloud.points[i].x = name;
	  // cout << "cloud " << cloud.points[i].x << endl;
	  // cout << "name  "<< name << endl;
     cloud.points[i].y = var1;
	  // cout << "c " << cloud.points[i].y << endl;
	  // cout << "var1 " << var1 << endl;
     cloud.points[i].z = var2;
	  // cout << "c " << cloud.points[i].z << endl;
	  // cout << "v2 " << var2 << endl;
     cloud.points[i].intensity = var3;
	  // cout << "i "<< cloud.points[i].intensity << endl;
	  // cout << "var3 "<< var3 << endl;
	  // cout << i << endl;
     ++i;
   }
   cout << "Writing point file" << endl;
   std::string f_name;
   f_name = "/home/ramrao/velodyne/fresh/obj" + boost::to_string(track) + ".pcd";
   cout << f_name << endl;

   pcl::io::savePCDFileASCII (f_name, cloud);
   std::cerr << "Saved " << cloud.points.size() << " data points " << f_name << std::endl;
   track += 1;
 }
 return(0);
}
