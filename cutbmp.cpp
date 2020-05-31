#include "inputProcessor.h"

int main(int argc, char** argv) {
	if (argc == 2 && !strcmp(argv[1], "/?")) {
		showHelp();
	}
	else if (numArg(argc, argv) != -1)
	{
		switch (numArg(argc, argv))
		{
		case 1:
			divide(argv[1], (int)strtol(argv[3], NULL, 10), 1);
			break;
		case 2:
			divide(argv[1], 1, (int)strtol(argv[3], NULL, 10));
			break;
		case 3:
			divide(argv[1], (int)strtol(argv[3], NULL, 10), (int)strtol(argv[5], NULL, 10));
			break;
		default:
			break;
		}
	}
	else {
		invalidInput();
	}
	return 0;
}