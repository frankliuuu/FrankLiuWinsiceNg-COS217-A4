/*--------------------------------------------------------------------*/
/* checkerDT.c                                                        */
/* Author: Frank Liu & Winsice Ng                                     */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "checkerDT.h"
#include "dynarray.h"
#include "path.h"

/* Iterates through oNNode's children and returns TRUE if 
   there are no duplicate paths. Return FALSE otherwise. */
static boolean CheckerDT_noDupPath(Node_T oNNode) {
      size_t tempChildIndex; 
      Node_T thisChild = NULL; 
      Node_T nextChild = NULL;
      for (tempChildIndex = 0; tempChildIndex < Node_getNumChildren(oNNode) - 1; tempChildIndex++) {
            int status1 = Node_getChild(oNNode, tempChildIndex, &thisChild);
            int status2 = Node_getChild(oNNode, tempChildIndex+1, &nextChild);
            if (status1 != SUCCESS || status2!= SUCCESS ) {
               fprintf(stderr, "getNumChildren claims more children than getChild returns\n");
               return FALSE;
            }
            Path_T currPath = Node_getPath(thisChild); 
            Path_T nextPath = Node_getPath(nextChild); 

            if (Path_comparePath(currPath, nextPath) == 0) {
                  return FALSE;
            } 
            /*else if (Path_comparePath(currPath, nextPath) > 0) 
               fprintf(stderr, "getNumChildren claims more children than getChild returns\n");
               return FALSE; */ 
         }

   return TRUE; 
}


/* see checkerDT.h for specification */
boolean CheckerDT_Node_isValid(Node_T oNNode) {
   Node_T oNParent;
   Path_T oPNPath;
   Path_T oPPPath;

   /* Sample check: a NULL pointer is not a valid node */
   if(oNNode == NULL) {
      fprintf(stderr, "A node is a NULL pointer\n");
      return FALSE;
   }

   /* Sample check: parent's path must be the longest possible
      proper prefix of the node's path */
   oNParent = Node_getParent(oNNode);
   if(oNParent != NULL) {
      oPNPath = Node_getPath(oNNode);
      oPPPath = Node_getPath(oNParent);

      if(Path_getSharedPrefixDepth(oPNPath, oPPPath) !=
         Path_getDepth(oPNPath) - 1) {
         fprintf(stderr, "P-C nodes don't have P-C paths: (%s) (%s)\n",
                 Path_getPathname(oPPPath), Path_getPathname(oPNPath));
         return FALSE;
      }
   }

   return TRUE;
}

/*
   Performs a pre-order traversal of the tree rooted at oNNode.
   Returns FALSE if a broken invariant is found and
   returns TRUE otherwise.

   You may want to change this function's return type or
   parameter list to facilitate constructing your checks.
   If you do, you should update this function comment.
*/
static boolean CheckerDT_treeCheck(Node_T oNNode) {
   size_t ulIndex;

   if(oNNode!= NULL) {

      /* Sample check on each node: node must be valid */
      /* If not, pass that failure back up immediately */
      if(!CheckerDT_Node_isValid(oNNode))
         return FALSE;

      /* Recur on every child of oNNode */
      for(ulIndex = 0; ulIndex < Node_getNumChildren(oNNode); ulIndex++)
      {
         Node_T oNChild = NULL; 
         int iStatus = Node_getChild(oNNode, ulIndex, &oNChild);
         
         if(iStatus != SUCCESS) {
            fprintf(stderr, "getNumChildren claims more children than getChild returns\n");
            return FALSE;
         }

      if (!CheckerDT_noDupPath(oNNode)) {
            fprintf(stderr, "two children of the same parent have the same path\n");
            return FALSE;
      }

         /* if recurring down one subtree results in a failed check
            farther down, passes the failure back up immediately */
         if(!CheckerDT_treeCheck(oNChild))
            return FALSE;
      }
   }
   return TRUE;
}

/* see checkerDT.h for specification */
boolean CheckerDT_isValid(boolean bIsInitialized, Node_T oNRoot,
                          size_t ulCount) {

   /* Sample check on a top-level data structure invariant:
      if the DT is not initialized, its count should be 0. */
   if(!bIsInitialized)
      if(ulCount != 0) {
         fprintf(stderr, "Not initialized, but count is not 0\n");
         return FALSE;
      }

   /* Now checks invariants recursively at each node from the root. */
   return CheckerDT_treeCheck(oNRoot);
}
