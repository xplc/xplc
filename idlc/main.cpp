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
  char* name;
  char* parent;
public:
  InterfaceNode(IDL_tree ident, IDL_tree inherit, IDL_tree body);
};

class MethodNode: public Node {
public:
  MethodNode(IDL_tree node);
};

Node::Node(): next(NULL) {
}

void showprops(const char* name, IDL_tree node) {
  if(IDL_NODE_PROPERTIES(node))
    printf("%s: %i properties\n", name, g_hash_table_size(IDL_NODE_PROPERTIES(node)));
  else
    printf("%s: no properties\n", name);
}

MethodNode::MethodNode(IDL_tree node) {
  printf("Method node: %s\n", IDL_IDENT(IDL_OP_DCL(node).ident).str);
}

InterfaceNode::InterfaceNode(IDL_tree ident,
                             IDL_tree inherit,
                             IDL_tree body): name(NULL),
                                             parent(NULL) {
  Node* head;
  Node* node;
  IDL_tree ptr;

  if(IDL_NODE_TYPE(ident) != IDLN_IDENT) {
    printf("InterfaceNode: ident is not an IDLN_IDENT!\n");
    exit(1);
  }

  name = IDL_IDENT(ident).str;

  if(inherit) {
    if(IDL_NODE_TYPE(inherit) != IDLN_LIST) {
      printf("InterfaceNode: inherit is not an IDLN_LIST!\n");
      exit(1);
    }

    if(IDL_LIST(inherit).next) {
      printf("InterfaceNode: multiple inheritance is forbidden\n");
      exit(1);
    }

    if(IDL_NODE_TYPE(IDL_LIST(inherit).data) != IDLN_IDENT) {
      printf("InterfaceNode: parent is not an IDLN_IDENT!\n");
      exit(1);
    }

    parent = IDL_IDENT(IDL_LIST(inherit).data).str;
  } else
    parent = NULL;

  if(body && (IDL_NODE_TYPE(body) != IDLN_LIST)) {
    printf("InterfaceNode: body is not an IDLN_LIST!\n");
    exit(1);
  }

  if(body) {
    head = Node::convertIdlToNode(IDL_LIST(body).data);
    node = head;
    ptr = IDL_LIST(body).next;
    while(ptr) {
      node->next = Node::convertIdlToNode(IDL_LIST(ptr).data);
      ptr = IDL_LIST(ptr).next;
    }
  }

  if(parent)
    printf("interface %s: %s\n", name, parent);
  else
    printf("interface %s\n", name);
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
  case IDLN_MODULE:
    printf("\"module\" keyword not supported!\n");
    exit(1);
    break;
  case IDLN_ATTR_DCL:
    printf("attributes not supported!\n");
    exit(1);
    break;
  case IDLN_OP_DCL:
    current = new MethodNode(tree);
    break;
  default:
    printf("Unknown node type (%s), aborting.\n", IDL_NODE_TYPE_NAME(tree));
    exit(1);
  }

  if(!current) {
    printf("convertIdlToNode is returning a null node!\n");
    exit(1);
  }

  return current;
}

void parse_file(const char* fn) {
  IDL_tree tree;
  Node* root;
  printf("parsing file %s\n", fn);
  IDL_parse_filename(fn, NULL, NULL, &tree, NULL, IDLF_PROPERTIES|IDLF_CODEFRAGS, IDL_WARNINGMAX);

  root = Node::convertIdlToNode(tree);
}

int main(unsigned int argc, char* argv[]) {
  unsigned int i;

  /* parse arguments */
  for(i = 1; i < argc; i++) {
    parse_file(argv[i]);
  }
}
