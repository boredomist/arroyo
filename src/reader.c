#include "reader.h"
#include <string.h>

void reader_create(reader* r, reader_fn fn, void* data)
{
  r->fn = fn;
  r->fn_data = data;

  r->available = 0;
  r->ptr = NULL;
}

int reader_fillbuf(reader* r)
{
  unsigned size;
  const char* buf = r->fn(r->fn_data, &size);

  if(buf == NULL || size == 0) {
    return EOS;
  }

  // size - 1 because last char is returned
  r->available = size - 1;
  r->ptr = buf;
  return *(r->ptr++);
}

int reader_getchar(reader* r)
{
  if(r->available-- > 0)
    return *(r->ptr++);

  return reader_fillbuf(r);
}

// the reader's fn_data must be freed manually
void string_reader_create(reader* r, char* string)
{
  r->fn = string_reader_read;

  string_reader_data* dat = malloc(sizeof(string_reader_data));
  dat->string = string;
  dat->read = 0;

  r->fn_data = dat;
  r->available = 0;
  r->ptr = NULL;
}

const char* string_reader_read(void* data, unsigned* size)
{
  string_reader_data* dat = data;

  if(dat->read) {
    *size = 0;
    return NULL;
  }
  dat->read = 1;
  *size = strlen(dat->string);
  return dat->string;
}
