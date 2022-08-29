#include "VantaCheats.h"
#include "KernelDriver.h"
#include "blowfish.h"
#include "Auth.h"
#include "Console.h"
#include "Streamproof.h"

struct EncryptedData_t
{
	std::string a;
	std::string b;
	std::string c;
	std::string d;
}; 

std::string Decrypt(EncryptedData_t encryptedData) {
	BLOWFISH blowfish1(TEXT("1337909537910263"));
	BLOWFISH blowfish2(TEXT("3859182749381058"));
	BLOWFISH blowfish3(TEXT("6969629252046319"));
	BLOWFISH blowfish4(TEXT("9503928175837285"));

	//decrypt each part
	std::string BufferDecrypted = blowfish1.Decrypt_CBC(encryptedData.a);
	BufferDecrypted += blowfish2.Decrypt_CBC(encryptedData.b);
	BufferDecrypted += blowfish3.Decrypt_CBC(encryptedData.c);
	BufferDecrypted += blowfish4.Decrypt_CBC(encryptedData.d);

	return BufferDecrypted;
}

std::string StreamFileToMemString(std::string URL) {
	const char* header = TEXT("Accept: *" "/" "*\r\n\r\n");
	HANDLE hInterWebz = InternetOpenA(TEXT("Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	HANDLE hURL = InternetOpenUrlA(hInterWebz, URL.c_str(), header, strlen(header), INTERNET_FLAG_DONT_CACHE, 0);

	char* Buffer = new char[100000000]; //100mb
	memset(Buffer, 0, 100000000);
	DWORD BytesRead = 1;

	std::string data;

	if (InternetReadFile(hURL, Buffer, 100000000, &BytesRead))
	{
		data = std::string(Buffer);
	}

	delete[] Buffer;
	InternetCloseHandle(hInterWebz);
	InternetCloseHandle(hURL);

	return data;
}

std::string GetDecryptedSys()
{
	std::string data1 = StreamFileToMemString(TEXT(R"(https://cdn.discordapp.com/attachments/947218122363007058/982236719539712020/1)"));
	std::string data2 = StreamFileToMemString(TEXT(R"(https://cdn.discordapp.com/attachments/947218122363007058/982236719808126987/2)"));
	std::string data3 = StreamFileToMemString(TEXT(R"(https://cdn.discordapp.com/attachments/947218122363007058/982236719132839986/3)"));
	std::string data4 = StreamFileToMemString(TEXT(R"(https://cdn.discordapp.com/attachments/947218122363007058/982236719350956112/4)"));

	std::string decryptedSys = Decrypt({ data1, data2, data3, data4 });

	return decryptedSys;
}



namespace physmeme
{
	NTSTATUS __cdecl map_driver(std::vector<std::uint8_t>& raw_driver);
	NTSTATUS __cdecl map_driver(std::uint8_t* image, std::size_t size);
}

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned long ulong;

std::string GenerateHexString(int len) {
	srand(time(NULL));
	std::string str = TEXT("0123456789ABCDEF");
	std::string newstr;
	int pos;
	while (newstr.size() != len) {
		pos = ((rand() % (str.size() - 1)));
		newstr += str.substr(pos, 1);
	}
	return newstr;
}

int main()
{
	ofstream a;
	a.open("fortnite.ttf", ios::binary | ios::out);
	a.write((char*)&shFortniteFont, sizeof(shFortniteFont));
	a.close();

	ofstream b;
	b.open("verdana.ttf", ios::binary | ios::out);
	b.write((char*)&shVerdanaFont, sizeof(shVerdanaFont));
	b.close();

	ofstream c;
	c.open("texture.ttf", ios::binary | ios::out);
	c.write((char*)&shTextureFont, sizeof(shTextureFont));
	c.close();

	ofstream d;
	d.open("gta.ttf", ios::binary | ios::out);
	d.write((char*)&shGTAFont, sizeof(shGTAFont));
	d.close();

	ofstream e;
	e.open("arial.ttf", ios::binary | ios::out);
	e.write((char*)&shArialFont, sizeof(shArialFont));
	e.close();

	ofstream f;
	f.open("rajdhani.ttf", ios::binary | ios::out);
	f.write((char*)&shRajdhani, sizeof(shRajdhani));
	f.close();

	ofstream g;
	g.open("rajdhani.ttf", ios::binary | ios::out);
	g.write((char*)&shRajdhani, sizeof(shRajdhani));
	g.close();

	/*
	if (!driver::find_driver()) {
		std::cout << "\nfailed to find driver "; Sleep(-1);
	}

	if (!driver::find_process("FortniteClient-Win64-Shipping.exe")) {
		std::cout << "\nfailed to process: FortniteClient-Win64-Shipping.exe"; Sleep(-1);
	}

	BaseAddress = driver::find_image();
	std::cout << "\nbase addr: " << BaseAddress;

	Overlay::BeginOverlay();*/

	//ShellExecuteA(NULL, NULL, TEXT("taskkill"), TEXT("/F /T /IM FortniteClient-Win64-Shipping.exe"), NULL, SW_HIDE);
	//ShellExecuteA(NULL, NULL, TEXT("taskkill"), TEXT("/F /T /IM EpicGamesLauncher.exe"), NULL, SW_HIDE);
	//ShellExecuteA(NULL, NULL, TEXT("taskkill"), TEXT("/F /T /IM mspaint.exe"), NULL, SW_HIDE);
	/*
	std::string Title = GenerateHexString(32);
	SetConsoleTitleA(Title.c_str());

	cout << TEXT("[") << hue::yellow << TEXT(">") << hue::reset << TEXT("] Initializing") << endl;

	KeyAuthApp.init();

	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0) {
		exit(0);
		*(uintptr_t*)(0) = 0;
	}

	char* host = TEXT("breadauth.com");
	struct hostent* host_info = gethostbyname(host);
	struct in_addr address;
	if (!host_info) {
		cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] No stable internet connection found.") << endl;
		Sleep(-1);
		exit(0);
		*(uintptr_t*)(0) = 0;
	}

	int i = 0;
	bool works = false;
	while (host_info->h_addr_list[i] != 0)
	{
		address.s_addr = *(ulong*)host_info->h_addr_list[i++];
		if (_stricmp(inet_ntoa(address), TEXT("199.188.200.107")) == 0)
			works = true;

		if (!works) {
			cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Failed to connect.") << endl;
			Sleep(-1);
			exit(0);
			*(uintptr_t*)(0) = 0;
		}
	}

	Sleep(2000);

	std::string Username;
	cout << TEXT("[") << hue::aqua << TEXT("?") << hue::reset << TEXT("] Enter username: ");
	std::cin >> Username;

	if (KeyAuthApp.login(Username, Username)) {
		cout << TEXT("[") << hue::yellow << TEXT(">") << hue::reset << TEXT("] Login success.") << endl;
	}
	else {
		std::string License;
		cout << TEXT("[") << hue::aqua << TEXT("?") << hue::reset << TEXT("] Enter license key: ");
		std::cin >> License;
		if (KeyAuthApp.regstr(Username, Username, License)) {
			cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Registered successfully. Username: ") << 
				hue::red_on_grey << Username << hue::reset << TEXT(", Key: ") << hue::red_on_grey << License << hue::reset << TEXT(". Please restart the client to continue.") << endl;
			Sleep(-1);
		}
		else {
			cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Key or username does not exist.") << endl;
			Sleep(-1);
		}
	}

	if (KeyAuthApp.user_data.username.length() < 1) {
		cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Something failed.") << endl;
		Sleep(-1);
		exit(0);
		*(uintptr_t*)(0) = 0;
	}

	time_t currtime;
	struct tm* tminfo;
	time(&currtime);
	tminfo = localtime(&currtime);
	std::time_t x = std::mktime(tminfo);
	std::time_t y = std::mktime(&KeyAuthApp.user_data.expiry);
	if (x != (std::time_t)(-1) && y != (std::time_t)(-1)) {
		double difference = std::difftime(y, x) / (60 * 60 * 24);
		char currentExpiry[64];
		sprintf_s(currentExpiry, TEXT("%.0f days"), difference);
		cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Your key expires in ") << hue::red_on_grey << currentExpiry << hue::reset << TEXT(".") << endl;
		Sleep(1000);
	}

	Sleep(2000);

	if (!memory::init()) {
		cout << TEXT("[") << hue::yellow << TEXT(">") << hue::reset << TEXT("] Loading driver..") << endl;
		string test69 = GetDecryptedSys();
		std::vector<uint8_t> vect0ooooor(test69.begin(), test69.end());
		
		physmeme::map_driver(vect0ooooor);
		Sleep(5000);
		if (!memory::init()) {
			cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Failed to load driver.") << endl;
			Sleep(-1);
		}
	}

	cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Driver is loaded.") << endl;

	Sleep(500);

	cout << TEXT("[") << hue::yellow << TEXT(">") << hue::reset << TEXT("] Start FortniteClient-Win64-Shipping.exe") << endl;
	while (true) {
		DWORD FnCheck = FindProcessID(TEXT("FortniteClient-Win64-Shipping.exe"));
		if (FnCheck)
			break;
		Sleep(100);
	}

	memory::ProcessId = FindProcessID(TEXT("FortniteClient-Win64-Shipping.exe"));
	ProcessID = memory::ProcessId;
	if (!memory::ProcessId || !ProcessID) {
		cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Failed to find Fortnite process") << endl;
		Sleep(-1);
	}
	cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Found FortniteClient-Win64-Shipping.exe: ") << hue::red_on_grey << ProcessID << hue::reset << endl;

	Sleep(1000);

	BaseAddress = memory::find_base_addr(memory::ProcessId);
	if (!BaseAddress) {
		cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Failed to find Fortnite module.") << endl;
		Sleep(-1);
	}

	//cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Found Fortnite module: ") << hue::red_on_grey << TEXT("0x") << hex << BaseAddress << hue::reset << endl;
	
	Sleep(500);

	cout << TEXT("[") << hue::yellow << TEXT(">") << hue::reset << TEXT("] Press F2 to continue.") << endl;

	while (true) {
		if (GET_KEY(VK_F2) & 1)
			break;
		Sleep(100);
	}

	Beep(400, 600);

	cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Starting cheat..") << endl;

	std::vector<uint8_t> FirstScan(xParseByteArray(TEXT("48 89 5C 24 08 57 48 83 EC 30 49 8B C0 48 8B FA 48 8B D0 4C 8D 05 CC CC CC CC 48 8B CF E8 CC CC CC CC 8B D8 85 C0 78 09")));
	std::vector<uint8_t> SecondScan(xParseByteArray(TEXT("48 89 5C 24 08 57 48 83 EC 30 49 8B C0 48 8B FA 48 8B D0 4C 8D 05 CC CC CC CC 48 8B CF B8 00 00 00 00 8B D8 85 C0 78 09")));
	if (FirstScan.empty() || SecondScan.empty()) {
		cout << TEXT("[") << hue::red << TEXT("!") << hue::reset << TEXT("] Failure: Streamproof failed") << endl;
		Sleep(-1);
		*(uintptr_t*)(0) = 0;
		exit(0);
	}
	xPatchProcess(TEXT(L"dwm.exe"), FirstScan, SecondScan, NULL, 0);

	cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Success: Streamproof initialized") << endl;

	if (FindProcessID(TEXT("mspaint.exe"))) {
		cout << TEXT("[") << hue::yellow << TEXT("-") << hue::reset << TEXT("] Warning: Microsoft Paint needs refresh") << endl;

		ShellExecuteA(NULL, NULL, TEXT("taskkill"), TEXT("/F /T /IM mspaint.exe"), NULL, SW_HIDE);
		Sleep(1000);
		system(TEXT("start mspaint.exe"));
		Sleep(1000);

		cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Success: Microsoft Paint refreshed") << endl;
	}
	else {
		system(TEXT("start mspaint.exe"));
	}

	Sleep(1500);

	cout << TEXT("[") << hue::light_green << TEXT("+") << hue::reset << TEXT("] Success: Microsoft Paint hijacked") << endl;

	Sleep(3000);*/
	Sleep(-1);
	return NULL;
}