#include <stdio.h>
#include <string.h>

typedef struct _fb
{
	unsigned char byte[4];
	unsigned int len;
	unsigned char depth;
} _fb;

_fb fb;

void outputFb( void )
{
	FILE *fp = fopen("output.fb", "wb2");
	if( fp )
	{
		unsigned int i;
		for( i = 0; i < fb.len; i++ )
		{
			switch( fb.depth )
			{
				case 1:
					fputc( fb.byte[0], fp );
					break;
				case 2:
					fputc( fb.byte[0], fp );
					fputc( fb.byte[1], fp );
					break;
				case 3:
					fputc( fb.byte[0], fp );
					fputc( fb.byte[1], fp );
					fputc( fb.byte[2], fp );
					break;
				case 4:
					fputc( fb.byte[0], fp );
					fputc( fb.byte[1], fp );
					fputc( fb.byte[2], fp );
					fputc( fb.byte[3], fp );
					break;
			}
		}
		fclose( fp );
	}
}

/*
	fb numbyte val1 val2 .. valn len
*/
int main( char argc, char *argv[] )
{
	char i;
	if( argc < 4 ) return 1;

	fb.depth = atoi(argv[1]);
	fb.len = atoi(argv[fb.depth+2]);

	for( i = 0; i < atoi(argv[1]); i++ )
	{
		fb.byte[i] = atoi(argv[i+2]);
	}

  outputFb();

  return 0;
}
