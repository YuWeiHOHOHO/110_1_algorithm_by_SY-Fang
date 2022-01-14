# 執行方式
1. 學號：B10730012
2. 姓名：張育瑋
3. 使用之程式語言：< C++ >
4. 使用之編譯平台：< Linux GNU g++ >
5. 檔案壓縮方式: <b10730012_張育瑋_PA2.rar>
6. 各檔案說明：
	 b10730012_張育瑋_PA2/PA2		: 主程式執行檔
	 b10730012_張育瑋_PA2/main.cpp		: 主程式source code
	 b10730012_張育瑋_PA2/graph.h		: library
	 b10730012_張育瑋_PA2/readme.txt	: 本檔案
7. 編譯方式說明：        	
   主程式：
	   在 b10730012_張育瑋_PA2這個資料夾下指令 : g++ -o PA2 main.cpp
	   即可產生 PA2 執行檔
	
8. 執行、使用方式說明：
   主程式：
   	   compile 完成後，在 /b10730012_張育瑋_PA2/ 目錄下會產生一個 PA2 的執行檔
   	   執行檔的命令格式為 :
   	   ./PA2 [input file name] [output file name]

	   ex: ./PA2 12.in 12.out

# 程式描述
這隻程式主要是Graph的實踐，內容大約是一張表格上會有n組對應的起終點，必須將他們用線相連，並每條邊的線是有數量上限的，超過就會overflow。
## 實踐
實踐上我使用 Dijkstra’s Shortest-Path Algorithm ，並在每條邊多一條線經過時使他的weight加一，並若線的數量超過上限，直接讓weight=INT_MAX。
