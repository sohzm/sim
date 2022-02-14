class Cursor {
    public: 
        int x, y, vu, vd, ox, oy, line;
        char mode;

        void move (int yl, int xl) {
            y += yl;
            x += xl;
        }
};
