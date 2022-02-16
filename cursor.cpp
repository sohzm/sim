class Cursor {
    public: 
        int line, pos, vline, vpos, oline, opos, vf, vl, lastline, lastline_lines, maxx;
        //  ^     ^    ^      ^     ^      ^     ^   ^   ^         ^               ^
        //  .     .    .      .     .      .     .   .   .         .               max value of x
        //  .     .    .      .     .      .     .   .   .         lines taken by lastline
        //  .     .    .      .     .      .     .   .   i forgor *_*         
        //  .     .    .      .     .      .     .   last line visible
        //  .     .    .      .     .      .     first line visible
        //  .     .    .      .     .      actual cur position on file
        //  .     .    .      .     actual cur line on file
        //  .     .    .      visual point position
        //  .     .    visual point line
        //  .     position of cursor
        //  line of cursor
        char mode;
};
