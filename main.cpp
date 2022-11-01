#include <iostream>
#include <string>

// ������������ ��������������� ������� LPS 
void computeLPS(const std::string& pat, size_t* lps)
{
    size_t j = 0;
    size_t i = 1;
    lps[0] = 0; // lps[0] ������ ����� 0
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0) {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// ������� �������� ��������� ������ K - ���������� �� ��������� ���
int IsKPeriodic(const std::string& str, int K)
{
    // K �� ������ ���� ����� 0 � 1, ������ �� ������ ���� ������, ����� ������ �� ������� �� � ��� �������, 
    // ��� ��������� � ������ ��� ����� �������� ������ 
    if ((K <= 1) || (str.empty()) || (str.size() % K) || (K >= str.size()))
    {
        return -1;
    }
    else
    {
        // ��������� ����������� �� ��������� �������� ������ � ���������� K
        std::string pat;
        for (size_t s = 0; s < K; ++s)
            pat.push_back(str[s]);

        size_t* lps = new size_t[pat.size()];

        // ����������� ������ lps
        computeLPS(pat, lps);

        size_t i = 0;
        size_t j = 0;
        int count = 0; // ���������� ��� �������� ��������� ��������� � �������� ������
        while (i < str.size()) {
            if (pat[j] == str[i])
            {
                j++;
                i++;
            }
            if (j == pat.size()) {
                // ���������� ������� - ����������� ������� ���������
                count++;
                j = lps[j - K];
            }
            else if (i < str.size() && pat[j] != str[i]) {
                if (j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    i = i + 1;
                }
            }
        }
        // ���� ���������� ��������� ����������, ����������� �� �, ����� ����� ������ - � ����� ������ ������ ������ �
        if ((static_cast<unsigned long long>(K) * count) == str.size())
            return 1;
        else
            return 0;

        delete[] lps;
    }
}

int main()
{
    std::string str; // �������� ������
    int K; // �������� ������ �� ��������� ����� �����
    char ans;

    bool exit = false;
    
    do
    {
        std::cout << "Enter input string: " << std::endl;
        std::getline(std::cin, str);
        std::cout << "Enter periodic (K): " << std::endl;
        std::cin >> K;
        
        if (IsKPeriodic(str, K) == -1)
        {
            std::cout << "Data entry error" << std::endl;
        }
        else if (IsKPeriodic(str, K))
        {
            std::cout << "Input string " << str << " and K = " << K << " is K - periodic" << std::endl;
        }
        else
        {
            std::cout << "Input string " << str << " and K = " << K << " is not K - periodic" << std::endl;
        }
       
        std::cout << "\nTry again (Y/N)?" << std::endl;
        std::cin >> ans;
        std::cin.ignore(32767, '\n');

        if (ans == 'N' || ans == 'n')
            exit = true;

    } while (!exit);

    return 0;
}