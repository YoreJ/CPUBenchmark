#include <bits/stdc++.h>
#include "PerfCounter.h"
#include "List_FindAndSort.h"
#include "Matrix.h"
#include "JPEG_Compress.h"
#include "SHA_256.h"
#include "XMLAnay.h"
#include "PrimeTest.h"
#include "Param.h"
#include "json.hpp"
#include "../../../../usr/include/c++/11/bits/algorithmfwd.h"
using namespace std;
using ll = long long;
using json = nlohmann::json;

void InfoShow(string& CurTest, Tuple& Result) 
{
    cout << CurTest << ":\n";
    cout << "\tCycle: " << get<0>(Result) << "\n";
    cout << "\tInstructions: " << get<1>(Result) << "\n";
    cout << "\tTime: " << get<2>(Result) << " ns\n";
    cout << "\tIPC: " << (double)get<1>(Result) / get<0>(Result) << "\n\n";
}

void ParamsInit(ParamType1& LsFind, ParamType1& LsSort, ParamType1& MulMatrix, ParamType1& HashParam, ParamType1& PrimeParam, ParamType2& XMLParam, ParamType3& JPEGParam) {
    ifstream file("config.json");
    if (!file.is_open()) return;
    json config_json;
    file >> config_json;
    file.close();
    if (!config_json.contains("configuration") || !config_json["configuration"].contains("tests")) return;
    for (const auto& test : config_json["configuration"]["tests"]) 
    {
        string testName = test.value("name", "");
        if (testName == "List_FindAndSort::FindTest") 
        {
            LsFind.Size = test["parameters"][0].value("value", 0);
            LsFind.Iter = test["parameters"][1].value("value", 0);
        } 
        else if (testName == "List_FindAndSort::SortTest") 
        {
            LsSort.Size = test["parameters"][0].value("value", 0);
            LsSort.Iter = test["parameters"][1].value("value", 0);
        } 
        else if (testName == "Matrix::MultiplyTest") 
        {
            MulMatrix.Size = test["parameters"][0].value("value", 0);
            MulMatrix.Iter = test["parameters"][1].value("value", 0);
        } 
        else if (testName == "JPEG_Compress::JPEGCompTest") 
        {
            JPEGParam.PathA = test["parameters"][0].value("value", "");
            JPEGParam.PathB = test["parameters"][1].value("value", "");
            JPEGParam.Qua = test["parameters"][2].value("value", 0);
            JPEGParam.Thrd = test["parameters"][3].value("value", 0);
            JPEGParam.Iteration = test["parameters"][4].value("value", 0);
            JPEGParam.Iter = test["parameters"][5].value("value", 0);
        } 
        else if (testName == "HashTest") 
        {
            HashParam.Size = test["parameters"][0].value("value", 0);
            HashParam.Iter = test["parameters"][1].value("value", 0);
        } 
        else if (testName == "XMLAnal") 
        {
            XMLParam.Path = test["parameters"][0].value("value", "");
            XMLParam.Iter = test["parameters"][1].value("value", 0);
        } 
        else if (testName == "Prime::PrimeTest") 
        {
            PrimeParam.Size = test["parameters"][0].value("value", 0);
            PrimeParam.Iter = test["parameters"][1].value("value", 0);
        }
    }
}

int main() 
{
    ParamType1 LsFind, LsSort, MulMatrix, HashParam, PrimeParam;
    ParamType2 XMLParam;
    ParamType3 JPEGParam;
    ParamsInit(LsFind, LsSort, MulMatrix, HashParam, PrimeParam, XMLParam, JPEGParam);
    cout << "LsFind: " << LsFind.Size << " " << LsFind.Iter << "\n";
    cout << "LsSort: " << LsSort.Size << " " << LsSort.Iter << "\n";
    cout << "MulMatrix: " << MulMatrix.Size << " " << MulMatrix.Iter << "\n";
    cout << "HashParam: " << HashParam.Size << " " << HashParam.Iter << "\n";
    cout << "PrimeParam: " << PrimeParam.Size << " " << PrimeParam.Iter << "\n";
    cout << "XMLParam: " << XMLParam.Path << " " << XMLParam.Iter << "\n";
    cout << "JPEGParam: " << JPEGParam.PathA << " " << JPEGParam.PathB << " " << JPEGParam.Qua << " " << JPEGParam.Thrd << " " << JPEGParam.Iteration << " " << JPEGParam.Iter << "\n\n";
    
    PerfCounter pc;
    Tuple Result;
    ll AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    bool EqualToStd = 1;
    json TestResult;
    
    // List_FindAndSort::Find
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "LsFind: " << 0 << " / " << LsFind.Iter << flush;
    for (int i = 0; i < LsFind.Iter; i++) 
    {
        Result = List_FindAndSort::FindTest(LsFind.Size, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "LsFind: " << i + 1 << " / " << LsFind.Iter << flush;
    }
    AvgCycle /= LsFind.Iter;
    AvgInst /= LsFind.Iter;
    AvgTime /= LsFind.Iter;
    cout << "\nLsFind:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["LsFind"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};

    // List_FindAndSort::Sort
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "LsSort: " << 0 << " / " << LsSort.Iter << flush;
    for (int i = 0; i < LsSort.Iter; i++) 
    {
        Result = List_FindAndSort::SortTest(LsSort.Size, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "LsSort: " << i + 1 << " / " << LsSort.Iter << flush;
    }
    AvgCycle /= LsSort.Iter;
    AvgInst /= LsSort.Iter;
    AvgTime /= LsSort.Iter;
    cout << "\nLsSort:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["LsSort"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};

    // Matrix::Multiply
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "MulMatrix: " << 0 << " / " << MulMatrix.Iter << flush;
    for (int i = 0; i < MulMatrix.Iter; i++) 
    {
        Result = Matrix::MultiplyTest(MulMatrix.Size, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "MulMatrix: " << i + 1 << " / " << MulMatrix.Iter << flush;
    }
    AvgCycle /= MulMatrix.Iter;
    AvgInst /= MulMatrix.Iter;
    AvgTime /= MulMatrix.Iter;
    cout << "\nMulMatrix:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["MulMatrix"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};
    
    // JPEGCompress
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "JPEGCompress: " << 0 << " / " << JPEGParam.Iter << flush;
    for (int i = 0; i < JPEGParam.Iter; i++) 
    {
        Result = JPEG_Compress::JPEGCompTest(JPEGParam.PathA, JPEGParam.PathB, JPEGParam.Qua, JPEGParam.Thrd, JPEGParam.Iteration, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "JPEGCompress: " << i + 1 << " / " << JPEGParam.Iter << flush;
    }
    AvgCycle /= JPEGParam.Iter;
    AvgInst /= JPEGParam.Iter;
    AvgTime /= JPEGParam.Iter;
    cout << "\nJPEGCompress:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["JPEGCompress"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};
    
    // SHA_256
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "SHA_256: " << 0 << " / " << HashParam.Iter << flush;
    for (int i = 0; i < HashParam.Iter; i++) 
    {
        Result = HashTest(HashParam.Size, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "SHA_256: " << i + 1 << " / " << HashParam.Iter << flush;
    }
    AvgCycle /= HashParam.Iter;
    AvgInst /= HashParam.Iter;
    AvgTime /= HashParam.Iter;
    cout << "\nSHA_256:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["SHA_256"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};
    
    // XMLAnalysis
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "XMLAnalysis: " << 0 << " / " << XMLParam.Iter << flush;
    for (int i = 0; i < XMLParam.Iter; i++) 
    {
        Result = XMLAnal(XMLParam.Path, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "XMLAnalysis: " << i + 1 << " / " << XMLParam.Iter << flush;
    }
    AvgCycle /= XMLParam.Iter;
    AvgInst /= XMLParam.Iter;
    AvgTime /= XMLParam.Iter;
    cout << "\nXMLAnalysis:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["XMLAnalysis"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};
    
    // PrimeTest
    AvgCycle = 0, AvgInst = 0, AvgTime = 0;
    cout << "PrimeTest: " << 0 << " / " << PrimeParam.Iter << flush;
    for (int i = 0; i < PrimeParam.Iter; i++) 
    {
        Result = Prime::PrimeTest(PrimeParam.Size, pc);
        AvgCycle += get<0>(Result);
        AvgInst += get<1>(Result);
        AvgTime += get<2>(Result);
        cout << "\r" << "PrimeTest: " << i + 1 << " / " << PrimeParam.Iter << flush;
    }
    AvgCycle /= PrimeParam.Iter;
    AvgInst /= PrimeParam.Iter;
    AvgTime /= PrimeParam.Iter;
    cout << "\nPrimeTest:\n";
    cout << "\tCycle: " << AvgCycle << "\n";
    cout << "\tInstructions: " << AvgInst << "\n";
    cout << "\tTime: " << AvgTime << " ns\n";
    cout << "\tIPC: " << (double)AvgInst / AvgCycle << "\n\n";
    TestResult["PrimeTest"] = {{"Cycle", AvgCycle}, {"Instructions", AvgInst}, {"Time", AvgTime}, {"IPC", (double)AvgInst / AvgCycle}};
    
    ofstream file("TestResult.json");
    if (file.is_open()) {
        file << TestResult.dump(4);
        file.close();
        cout << "数据已写入TestResult.json文件。" << endl;
    } else {
        cerr << "无法打开文件进行写入。" << endl;
    }
}