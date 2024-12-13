class wifi{
    private:
        wifi();

    public:
        static wifi* getInstance();

        bool init();
        void print();
};