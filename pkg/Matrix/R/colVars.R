

setGeneric("colVars", function(x, na.rm = FALSE, ...){
  standardGeneric("colVars")
})

setMethod("colVars", signature = "ANY", function(x, na.rm=FALSE, ...){
  stop("colVars() is not defined for x of class: ", paste0(class(x), collapse = ", "))  
})


setMethod("colVars", signature = "matrix", function(x, na.rm=FALSE, ...){
  if(requireNamespace("matrixStats", quietly = TRUE)){
    matrixStats::colVars(x, na.rm=na.rm, ...)
  }else{
    stop("colVars() for x of class matrix, requires the 'matrixStats' package.\n",
         "You can install it with 'install.packages(\"matrixStats\")'.")
  }
})

setMethod("colVars", signature = "denseMatrix", function(x, na.rm=FALSE, ...){
  if(requireNamespace("matrixStats", quietly = TRUE)){
    matrixStats::colVars(as(Mat, "matrix"), na.rm=na.rm, ...)
  }else{
    stop("colVars() for x of class denseMatrix, requires the 'matrixStats' package.\n",
         "You can install it with 'install.packages(\"matrixStats\")'.")
  }
})


setMethod("colVars", signature = "dgCMatrix", function(x, na.rm=FALSE, ...){
  if(requireNamespace("sparseMatrixStats", quietly = TRUE)){
    sparseMatrixStats::colVars(x, na.rm=na.rm, ...)
  }else{
    stop("colVars() for x of class dgCMatrix, requires the 'sparseMatrixStats' package.\n",
         "You can install it with 'install.packages(\"sparseMatrixStats\")'.")
  }
})



