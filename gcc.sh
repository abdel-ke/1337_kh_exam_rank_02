if ! test -f pft_exam/Makefile; then
	git clone https://github.com/gavinfielder/pft.git pft_exam && echo "pft_exam/" >> .gitignore && cd pft_exam && rm unit_tests.c && rm options-config.ini && git clone https://github.com/cclaude42/PFT_EXAM.git temp && cp temp/unit_tests.c . && cp temp/options-config.ini . && rm -rf temp
	cd ../
fi
gcc -c ft_printf.c && ar rc libftprintf.a ft_printf.o && cd pft_exam && make && ./test $1 && cd ../ && rm *.o libftprintf.a
