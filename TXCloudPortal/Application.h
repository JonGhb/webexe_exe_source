#pragma once

#include <string>

class Application
{
protected:
    Application();
    Application(const Application&);
    Application& operator =(const Application&);
public:
    virtual ~Application();
    static Application& instance();

    int run(int &argc, char **argv);
    void quit(int retcode = 0);

    bool openAndWait(const std::string& jsonUTF8); // αЭ����������Э���ʽTXCloudRoom://liteav/params?json={}
private:
    void showNormalLiveByCommandLine(int &argc, char **argv);

    bool regProtol();   // ע���ע��αЭ��
};
