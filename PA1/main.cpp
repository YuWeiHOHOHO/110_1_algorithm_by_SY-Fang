#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

void getMaxChord(int i, int j, int &numPoints, vector<int> chords, vector<int> &maxChord, vector<vector<int>> &MIS) {
    //找maxChord
    while (MIS.at(i).at(j) > 0) {

        int k = chords.at(j);

        if (j - 1 == 1) {
            maxChord.push_back(i);
            break;
        }else if (k == i) { //Case3
            maxChord.push_back(i);
            i++;
            j--;
        }
        else if (k > j || k < i) { //Case1
            j--;
        }
        else if (i < k < j) { //Case2
            if (MIS.at(i).at(j - 1) > MIS.at(i).at(k - 1) + 1 + MIS.at(k + 1).at(j - 1)) {
                j--;
            }
            else {
                getMaxChord(i, k - 1, numPoints, chords, maxChord, MIS);
                maxChord.push_back(k);
                getMaxChord(k+1, j - 1, numPoints, chords, maxChord, MIS);
                break;
            }
        }
        else {
            cout << "maxChord case error";
        }
    }
}

int main(int argc, char** argv)
{
    cout << "start!!" << endl;
    //input error
    if (argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        //    system("pause");
        exit(1);
    }

    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    if (!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    // parse the input file
    char buffer[100];
    fin >> buffer;
    int numPoints = atoi(buffer);// 全部有幾個點

    // 存弦的兩點
    vector<int> chords;
    chords.resize(numPoints);

    // 弦數矩陣
    vector<vector<int>> MIS;
    MIS.resize(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        MIS.at(i).resize(numPoints);
    }

    //紀錄最大數弦
    vector<int> maxChord;

    for (int i = 0; i < numPoints / 2; ++i)
    {
        fin >> buffer;
        int point1 = atoi(buffer);
        fin >> buffer;
        int point2 = atoi(buffer);
        chords.at(point1) = point2;
        chords.at(point2) = point1;
    }

    //建MIS表格
    for (int p = 0; p < numPoints; ++p) { // p = 加幾格
        for (int i = 0; i < numPoints; i++) { //i = 從第幾格開始框
            pair<int, int> tempChord;
            int j = i + p;
            
            if (j < numPoints) {
                int k = chords.at(j);

                if (p == 0) {
                    MIS.at(i).at(j) = 0;
                }
                else if (p == 1) {
                    if (chords.at(i) == j) {
                        MIS.at(i).at(j) = 1;
                    }
                }
                else { //p>=2
                    if (k == i) { //Case3
                        MIS.at(i).at(j) = 1 + MIS.at(i + 1).at(j - 1);
                    }
                    else if (k > j || k < i) { //Case1
                        MIS.at(i).at(j) = MIS.at(i).at(j - 1);
                    }
                    else if (i < k < j) { //Case2
                        if (MIS.at(i).at(j - 1) > MIS.at(i).at(k - 1) + 1 + MIS.at(k + 1).at(j - 1)) {
                            MIS.at(i).at(j) = MIS.at(i).at(j - 1);
                        }
                        else {
                            MIS.at(i).at(j) = MIS.at(i).at(k - 1) + 1 + MIS.at(k + 1).at(j - 1);
                        }
                    }
                    else {
                        cout << "MIS case error";
                    }
                }
            }

            else {
                break;
            }
        }
    }

    getMaxChord(0, numPoints - 1, numPoints, chords, maxChord, MIS);

    // open the output file
    fstream fout;
    fout.open(argv[2], fstream::out);
    if (!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
        exit(1);
    }
    // output something to the output file
    fout << MIS.at(0).at(numPoints-1) << endl;
    for (int i = 0; i < maxChord.size(); i++) {
        fout << maxChord.at(i) << " " << chords.at(maxChord.at(i)) << endl;
    }

    cout << "finished!!" << endl;
    return 0;
}