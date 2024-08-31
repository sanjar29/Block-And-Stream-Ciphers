#include <iostream>
#include <vector>
using namespace std;

int main() {
    string input = "ABCDEFGHIJKLMNOP";
    cout << "**Encrypt**\n" << input << '\n';
    string key = "COMPUTER76543210";
            vector<char> data(input.begin(), input.end());
    		vector<char>::iterator start = data.begin();
			vector<char>::iterator end = data.end() - 1;
			while (start < end) {
				for (char byte : key) {
					bool swap = byte % 2;
					if (swap) {
						iter_swap(start, end);
						end--;
					}
					start++;
					string output(data.begin(), data.end());
					cout << output << '\n';
					if (start >= end) {
						break;
					}
				}
			}
			
			cout << "**Decrypt**\n";
			string beginningData(data.begin(), data.end());
			cout << beginningData << '\n';
			
start = data.end() - 1;
end = data.begin();

while (start > end) {
    for (char byte : key) {
        bool swap = byte % 2;
        if (swap) {
            iter_swap(start, end);
            start--;
        }
        end++;
        string output(data.begin(), data.end());
        cout << output << '\n';
        if (start <= end) {
            break;
        }
    }
}
    return 0;
}
