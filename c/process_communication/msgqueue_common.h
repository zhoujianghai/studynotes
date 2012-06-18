#define TEXT_SIZE 2048

typedef struct
{
	long msg_type;
	char msg_text[TEXT_SIZE];
}msg_queue;
