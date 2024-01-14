# UTF-8-Decoder

UTF-8-Decoder is a compact and very simple C program that extracts all the code points from a UTF-8 encoded file.
Developed primarily for my own personal research into the intricacies of UTF-8. While not designed for general usage, I am sharing this program with the hope that it may assist others in their learning and exploration of UTF-8. 
## Download and Compilation
### Prerequisites:
- git
- gcc
- make

Clone the repository and run the Makefile:
```shell
git clone https://github.com/ThomasWaytec/UTF-8-Decoder.git
cd ./UTF-8-Decoder
make
```

## Usage
Type in ```./utf8``` followed by the name of the file you'd like to analyze.  

### Examples:
``` shell
./utf8 symbols.txt
./utf8 README.md
./utf8 page.html

```
