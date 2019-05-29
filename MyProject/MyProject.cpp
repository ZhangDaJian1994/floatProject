// MyProject.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
//#include <iRRAM/lib.h>
//using namespace iRRAM;

///*
//一元指令存储结构
//*/
//struct
//{
//	REAL x1;
//	REAL x2;
//	std::string formula;
//}oneDimInterval;
//
///*
//二元指令存储结构
//*/
//struct
//{
//	REAL x1;
//	REAL x2;
//	REAL y1;
//	REAL y2;
//	std::string formula;
//}twoDimInterval;
/*
获取指令类型
*/

bool isMachineCode(std::string instruct) {
	bool flag = true;
	std::string::iterator ite;
	ite = instruct.begin();
	for (; ite != instruct.end(); ite++) {
		if (*ite != '0' || *ite != '1') {
			flag = false;
			break;
		}
	}
	return flag;
}

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

//enum AssemblyInstuct { FADD, FSUB, FMUL, FDIV, FSQRT };
std::string AssemblyInstuct[5] = {"FADD","FSUB", "FMUL", "FDIV", "FSQRT"};
bool isAssemblyCode(std::string instruct) {
	std::vector<std::string> v;
	SplitString(instruct, v, " ");
	for (int i = 0; i < 5; i++) {
		if (v[0] == AssemblyInstuct[i]) {
			return true;
		}
	}
	return false;
}

bool isStringExpression(std::string instruct) {
	return true;
}

void generateCpp(std::string instruct) {
		
}
void generateCppFloat(std::string instruct) {
	std::ofstream ofile;               //定义输出文件
	ofile.open("d:\\testFloat.cpp");     //作为输出文件打开
	ofile << "#include <iostream>                   " << std::endl;
	ofile << "#include <stdlib.h>                   " << std::endl;
	ofile << "#include <fstream>                    " << std::endl;
	ofile << "int main(int argc,char *argv[]) {     " << std::endl;
	ofile << "float res,x,y;                        " << std::endl;
	ofile << "if(argc == 2){                        " << std::endl;
	ofile << "x=atof(argv[1]);                      " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile << "else if (argc == 3) {                 " << std::endl;
	ofile << "x=atof(argv[1]);                      " << std::endl;
	ofile << "y=atof(argv[2]);                      " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile << "res="+instruct+";"                          << std::endl;
	ofile << "std::ofstream ofile;                  " << std::endl;
	ofile << "ofile.open(\"d:\\\\floatOut.txt\");   " << std::endl;
	ofile << "ofile << res << \"\\n\";           " << std::endl;
	ofile << "ofile.close();                        " << std::endl;
	ofile << "}                                     " << std::endl;
	ofile.close();
	system("g++ d:\\testFloat.cpp -c -o d:\\testFloat.o -I d:\\project\\irramlib\\include\\");
	system("g++ -o d:\\testFloat.exe d:\\testFloat.o");
	std::cout << " 请输入参数" << std::endl;
	std::string argv;
	std::getline(std::cin, argv);
	std::string command = "d:\\testFloat.exe " + argv;
	system(command.data());
}
void generateCppReal(std::string instruct) {
	std::ofstream ofile;               //定义输出文件
	ofile.open("d:\\testReal.cpp");     //作为输出文件打开
	ofile << "#include \"iRRAM/lib.h\"                                                            " << std::endl;
	ofile << "#include \"iRRAM/core.h\"                       " << std::endl;
	ofile << "#include <string>                                                                 " << std::endl;
	ofile << "#include<fstream>                                                                 " << std::endl;
	ofile << "using namespace iRRAM;                                                            " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int iRRAM_compute(int argc, char **argv) {                                        " << std::endl;
	ofile << "REAL res,x,y;                                                                     " << std::endl;
	ofile << "if (argc == 2){                                                                   " << std::endl;
	ofile << "	x = argv[1];                                                                    " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "else if (argc == 3){                                                              " << std::endl;
	ofile << "	x = argv[1];                                                                    " << std::endl;
	ofile << "	y = argv[2];                                                                    " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "res = " << instruct << ";"                                                                 << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int deci_places;                                                                  " << std::endl;
	ofile << "cout << \"please input deci_places: \" ;                                                      " << std::endl;
	ofile << "cin >> deci_places;                                                               " << std::endl;
	ofile << "string result = swrite(res,deci_places+8);                                        " << std::endl;
	ofile << "std::ofstream ofile;                                                           " << std::endl;
	ofile << "ofile.open(\"d:\\\\realOut.txt\");                                                           " << std::endl;
	ofile << "ofile << result << \"\\n\";                                                            " << std::endl;
	ofile << "ofile.close();                                                            " << std::endl;
	ofile << "return 0;                                                                         " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "template int iRRAM_exec <int,char **,int> (int (*) (int,char **),int, char **);   " << std::endl;
	ofile << "                                                                                  " << std::endl;
	ofile << "int main(int argc,char **argv) {                                                  " << std::endl;
	ofile << "iRRAM_initialize(argc,argv);                                                      " << std::endl;
	ofile << "iRRAM_exec(iRRAM_compute,argc,argv);                                              " << std::endl;
	ofile << "return 0;                                                                         " << std::endl;
	ofile << "}                                                                                 " << std::endl;
	ofile.close();
	system("g++ d:\\testReal.cpp -c -o d:\\testReal.o -I d:\\project\\irramlib\\include\\");
	system("g++ -o d:\\testReal.exe d:\\testReal.o d:\\project\\irramlib\\lib\\libiRRAM.a d:\\project\\irramlib\\lib\\libmpfr.a d:\\project\\irramlib\\lib\\libgmp.a");
	std::cout << " 请输入参数" << std::endl;
	std::string argv;
	std::getline(std::cin, argv);
	std::string command = "d:\\testReal.exe " + argv;
	system(command.data());
}

void machineToAssembly(std::string instruct) {

}

void assemblyToStringExpression(std::string instruct) {

}
void printRes() {

}


int getInstructType(std::string instruct) {
	if (isMachineCode(instruct)) {	//是机器码
		return 0;
	}
	else if (isAssemblyCode(instruct)) { //是汇编代码
		return 1;
	}
	else if (isStringExpression(instruct)) {	//是string 表达式
		return 2;
	}
	else {
		return -1;
	}
}
/*
遍历浮点数
*/
void traverseFloat() {

}


int main()
{
	printf("%s\n", "请输入指令");
	std::string instruction;
	int a;
	std::getline(std::cin, instruction);
	generateCppReal(instruction);	
	generateCppFloat(instruction);
	//int instructType = getInstructType(instruction);
	//// 1. 判断指令类型
	////    如果是机器码，转2
	////	  如果是汇编码，转3
	////	  如果是字符串，转4
	//if (instructType == 0) { // 0 ---> 机器码
	//	//2. 机器码转汇编码
	//	machineToAssembly(instruction);
	//}
	//else if (instructType == 1) {	// 1 ---> 汇编码
	//	
	//	//3. 汇编转字符串表达式
	//	assemblyToStringExpression(instruction);
	//}
	//else if (instructType == 2) {	// 2 ---> 字符串表达式
	//	//4. 生成cpp文件，编译运行
	//	//4-1 生成编译后的cpp程序
	//	generateCpp(instruction);
	//	//4-2 判断指令是几元？
	//	analysisInstruction(instruction);
	//	//4-3 遍历浮点
	//	traverseFloat();	//如何获取两个浮点之间的中间点
	//}




	//else {			//指令类型不存在，结束程序
	//	exit(1);
	//}
	////std::cout << instruction << std::endl;
	system("pause");
}