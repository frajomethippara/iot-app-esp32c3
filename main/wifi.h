#include <cstring>

class wifi{
    private:
        wifi();

    public:
        static wifi* getInstance();

        bool init();
        bool connect(char *, char *);
        bool disconnect();
        void print();
};