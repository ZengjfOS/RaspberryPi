all:
	gcc example.c wavfile.c -o wavfile -lm
clean:
	rm wavfile
	rm sound.wav 
