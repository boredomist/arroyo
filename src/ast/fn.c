#include "ast.h"
#include "util.h"
#include "buffer.h"

fn_node* fn_node_create()
{
  fn_node* fn = malloc(sizeof(fn_node));
  fn->id = NULL;

  fn->nargs = 0;
  fn->args = malloc(0);
  fn->body = NULL;

  return fn;
}

void fn_node_destroy(fn_node* fn)
{
  if(fn->id)
    free(fn->id);

  for(unsigned i = 0; i < fn->nargs; ++i) {
    free(fn->args[i].id);
  }
  if(fn->args)
    free(fn->args);

  if(fn->body)
    expression_node_destroy(fn->body);

  free(fn);
}

expression_node* fn_node_evaluate(fn_node* fn, scope* scope)
{
  // TODO
  return NULL;
}

fn_node* fn_node_clone(fn_node* fn)
{
  // TODO
  return NULL;
}

char* fn_node_to_string(fn_node* fn)
{
  buffer b;
  buffer_create(&b, 10);

  buffer_puts(&b, "fn ");
  buffer_puts(&b, fn->id ? fn->id : "<fn>");

  buffer_puts(&b, " (");
  for(unsigned i = 0; i < fn->nargs; ++i) {
    buffer_puts(&b, fn->args[i].id);
    if(fn->args[i].arg_type != -1) {
      buffer_putc(&b, ':');
      buffer_puts(&b, node_type_string[fn->args[i].arg_type]);
    }
    if(i != fn->nargs - 1) buffer_putc(&b, ' ');
  }
  buffer_puts(&b, ") ");

  char* body = expression_node_to_string(fn->body);
  buffer_puts(&b, body);
  free(body);

  buffer_putc(&b, '\0');

  return b.buf;
}

char* fn_node_inspect(fn_node* fn)
{
  buffer b;
  buffer_create(&b, 10);

  buffer_puts(&b, "fn ");
  buffer_puts(&b, fn->id ? fn->id : "<fn>");

  buffer_puts(&b, " (");
  for(unsigned i = 0; i < fn->nargs; ++i) {
    buffer_puts(&b, fn->args[i].id);
    if(fn->args[i].arg_type != -1) {
      buffer_putc(&b, ':');
      buffer_puts(&b, node_type_string[fn->args[i].arg_type]);
    }
    if(i != fn->nargs - 1)
      buffer_putc(&b, ' ');
  }
  buffer_puts(&b, ") ");

  char* body = expression_node_inspect(fn->body);
  buffer_puts(&b, body);
  free(body);

  buffer_putc(&b, '\0');

  return b.buf;
}


void fn_node_add_argument(fn_node* fn, char* name, int type)
{
  fn->args = realloc(fn->args, sizeof(struct typed_id) * ++fn->nargs);
  fn->args[fn->nargs - 1] = (struct typed_id) {
    .id = strdup(name),
    .arg_type = type
  };
}
