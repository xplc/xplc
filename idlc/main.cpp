/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * XPLC - Cross-Platform Lightweight Components
 * Copyright (C) 2000, Pierre Phaneuf
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License
 * as published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#include <stdio.h>
#include <libIDL/IDL.h>

class Node {
public:
  Node* next;
  static Node* convertIdlToNode(IDL_tree);
  Node();
};

class InterfaceNode: public Node {
private:
  IDL_tree parent;
public:
  InterfaceNode(IDL_tree ident, IDL_tree inherit, IDL_tree body);
};

Node::Node(): next(NULL) {
}

InterfaceNode::InterfaceNode(IDL_tree ident,
			     IDL_tree inherit,
			     IDL_tree body) {
  if(IDL_NODE_TYPE(ident) != IDLN_IDENT) {
    printf("InterfaceNode: ident is not an IDLN_IDENT!\n");
    exit(1);
  }

  if(inherit) {
    if(IDL_NODE_TYPE(inherit) != IDLN_LIST) {
      printf("InterfaceNode: inherit is not an IDLN_LIST!\n");
      exit(1);
    }

    if(IDL_LIST(inherit).next) {
      printf("InterfaceNode: multiple inheritance is forbidden\n");
      exit(1);
    }

    parent = IDL_LIST(inherit).data;
    printf("parent is %s\n", IDL_NODE_TYPE_NAME(parent));
  } else
    parent = NULL;

  if(body && (IDL_NODE_TYPE(body) != IDLN_LIST)) {
    printf("InterfaceNode: body is not an IDLN_LIST!\n");
    exit(1);
  }

  if(parent)
    printf("interface %s: public %s\n", IDL_IDENT(ident).str, IDL_IDENT(parent).str);
  else
    printf("interface %s\n", IDL_IDENT(ident).str);
}

Node* Node::convertIdlToNode(IDL_tree tree) {
  Node* current;
  Node* tmp;
  IDL_tree ptr;

  if(!tree) {
    printf("convertIdlToNode was passed a null node!\n");
    exit(1);
  }

  switch(IDL_NODE_TYPE(tree)) {
  case IDLN_LIST:
    current = convertIdlToNode(IDL_LIST(tree).data);
    tmp = current;
    ptr = IDL_LIST(tree).next;
    while(ptr && tmp) {
      tmp->next = convertIdlToNode(IDL_LIST(ptr).data);
      tmp = tmp->next;
      ptr = IDL_LIST(ptr).next;
    }
    break;
  case IDLN_INTERFACE:
    current = new InterfaceNode(IDL_INTERFACE(tree).ident,
				IDL_INTERFACE(tree).inheritance_spec,
				IDL_INTERFACE(tree).body);
    break;
  default:
    printf("Unknown node type (%s), aborting.\n", IDL_NODE_TYPE_NAME(tree));
    exit(1);
  }

  return current;
}

void parse_file(const char* fn) {
  IDL_tree tree;
  Node* root;
  printf("parsing file %s\n", fn);
  IDL_parse_filename(fn, NULL, NULL, &tree, NULL, 0, IDL_WARNINGMAX);

  root = Node::convertIdlToNode(tree);
}

int main(unsigned int argc, char* argv[]) {
  unsigned int i;

  /* parse arguments */
  for(i = 1; i < argc; i++) {
    parse_file(argv[i]);
  }
}
