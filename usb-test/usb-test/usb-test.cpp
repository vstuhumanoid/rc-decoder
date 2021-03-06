#include <iostream>
#include "hidapi.h"
#include <Windows.h>

using namespace std;
#define MAX_STR 255

int main()
{
	hid_device* handle;
	unsigned char buf[65];
	wchar_t wstr[MAX_STR];

	
	hid_init();
	handle = hid_open(0x0483, 0x5750, NULL);
	if(handle == NULL)
	{
		cout << "Device not connected\n";
		return -1;
	}
	

	// Read the Manufacturer String
	hid_get_manufacturer_string(handle, wstr, MAX_STR);
	wcout << L"Manufacturer String: " <<  wstr << endl;

	// Read the Product String
	hid_get_product_string(handle, wstr, MAX_STR);
	wcout << L"Product String: " << wstr << endl;

	// Read the Serial Number String
	hid_get_serial_number_string(handle, wstr, MAX_STR);
	wcout << L"Serial Number String: (" << (int)wstr[0] << ") " << wstr << endl;

	// Read Indexed String 1
	hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	wcout << L"Indexed String 1: " << wstr << endl;

	while (true)
	{
		int bytes = hid_read(handle, buf, 65);

		cout << "Received: " << bytes << endl;
		for (int i = 0; i < bytes; i++)
			cout << (int)buf[i] << " ";

		cout << endl;
	}

	hid_close(handle);


    return 0;
}

