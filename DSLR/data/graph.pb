
C
inputPlaceholder* 
shape:?????????*
dtype0
D
targetPlaceholder*
dtype0* 
shape:?????????
?
-dense/kernel/Initializer/random_uniform/shapeConst*
valueB"      *
_class
loc:@dense/kernel*
dtype0
y
+dense/kernel/Initializer/random_uniform/minConst*
valueB
 *׳ݿ*
_class
loc:@dense/kernel*
dtype0
y
+dense/kernel/Initializer/random_uniform/maxConst*
valueB
 *׳??*
_class
loc:@dense/kernel*
dtype0
?
5dense/kernel/Initializer/random_uniform/RandomUniformRandomUniform-dense/kernel/Initializer/random_uniform/shape*
T0*
_class
loc:@dense/kernel*
dtype0*
seed2 *

seed 
?
+dense/kernel/Initializer/random_uniform/subSub+dense/kernel/Initializer/random_uniform/max+dense/kernel/Initializer/random_uniform/min*
T0*
_class
loc:@dense/kernel
?
+dense/kernel/Initializer/random_uniform/mulMul5dense/kernel/Initializer/random_uniform/RandomUniform+dense/kernel/Initializer/random_uniform/sub*
T0*
_class
loc:@dense/kernel
?
'dense/kernel/Initializer/random_uniformAddV2+dense/kernel/Initializer/random_uniform/mul+dense/kernel/Initializer/random_uniform/min*
T0*
_class
loc:@dense/kernel
?
dense/kernel
VariableV2*
shared_name *
_class
loc:@dense/kernel*
dtype0*
	container *
shape
:
?
dense/kernel/AssignAssigndense/kernel'dense/kernel/Initializer/random_uniform*
use_locking(*
T0*
_class
loc:@dense/kernel*
validate_shape(
U
dense/kernel/readIdentitydense/kernel*
T0*
_class
loc:@dense/kernel
l
dense/bias/Initializer/zerosConst*
valueB*    *
_class
loc:@dense/bias*
dtype0
y

dense/bias
VariableV2*
shape:*
shared_name *
_class
loc:@dense/bias*
dtype0*
	container 
?
dense/bias/AssignAssign
dense/biasdense/bias/Initializer/zeros*
validate_shape(*
use_locking(*
T0*
_class
loc:@dense/bias
O
dense/bias/readIdentity
dense/bias*
_class
loc:@dense/bias*
T0
B
dense/Tensordot/axesConst*
valueB:*
dtype0
I
dense/Tensordot/freeConst*
dtype0*
valueB"       
>
dense/Tensordot/ShapeShapeinput*
T0*
out_type0
G
dense/Tensordot/GatherV2/axisConst*
dtype0*
value	B : 
?
dense/Tensordot/GatherV2GatherV2dense/Tensordot/Shapedense/Tensordot/freedense/Tensordot/GatherV2/axis*
Taxis0*

batch_dims *
Tindices0*
Tparams0
I
dense/Tensordot/GatherV2_1/axisConst*
value	B : *
dtype0
?
dense/Tensordot/GatherV2_1GatherV2dense/Tensordot/Shapedense/Tensordot/axesdense/Tensordot/GatherV2_1/axis*
Taxis0*

batch_dims *
Tindices0*
Tparams0
C
dense/Tensordot/ConstConst*
valueB: *
dtype0
s
dense/Tensordot/ProdProddense/Tensordot/GatherV2dense/Tensordot/Const*
T0*

Tidx0*
	keep_dims( 
E
dense/Tensordot/Const_1Const*
valueB: *
dtype0
y
dense/Tensordot/Prod_1Proddense/Tensordot/GatherV2_1dense/Tensordot/Const_1*

Tidx0*
	keep_dims( *
T0
E
dense/Tensordot/concat/axisConst*
value	B : *
dtype0
?
dense/Tensordot/concatConcatV2dense/Tensordot/freedense/Tensordot/axesdense/Tensordot/concat/axis*
T0*
N*

Tidx0
i
dense/Tensordot/stackPackdense/Tensordot/Proddense/Tensordot/Prod_1*
T0*

axis *
N
[
dense/Tensordot/transpose	Transposeinputdense/Tensordot/concat*
Tperm0*
T0
k
dense/Tensordot/ReshapeReshapedense/Tensordot/transposedense/Tensordot/stack*
T0*
Tshape0
{
dense/Tensordot/MatMulMatMuldense/Tensordot/Reshapedense/kernel/read*
transpose_a( *
transpose_b( *
T0
E
dense/Tensordot/Const_2Const*
valueB:*
dtype0
G
dense/Tensordot/concat_1/axisConst*
value	B : *
dtype0
?
dense/Tensordot/concat_1ConcatV2dense/Tensordot/GatherV2dense/Tensordot/Const_2dense/Tensordot/concat_1/axis*
T0*
N*

Tidx0
c
dense/TensordotReshapedense/Tensordot/MatMuldense/Tensordot/concat_1*
T0*
Tshape0
Z
dense/BiasAddBiasAdddense/Tensordotdense/bias/read*
T0*
data_formatNHWC
*
outputIdentitydense/BiasAdd*
T0
#
subSuboutputtarget*
T0

SquareSquaresub*
T0
>
ConstConst*!
valueB"          *
dtype0
A
lossMeanSquareConst*
T0*

Tidx0*
	keep_dims( 
8
gradients/ShapeConst*
valueB *
dtype0
F
gradients/grad_ys_0/ConstConst*
valueB
 *  ??*
dtype0
b
gradients/grad_ys_0Fillgradients/Shapegradients/grad_ys_0/Const*
T0*

index_type0
Z
!gradients/loss_grad/Reshape/shapeConst*!
valueB"         *
dtype0
u
gradients/loss_grad/ReshapeReshapegradients/grad_ys_0!gradients/loss_grad/Reshape/shape*
T0*
Tshape0
C
gradients/loss_grad/ShapeShapeSquare*
T0*
out_type0
s
gradients/loss_grad/TileTilegradients/loss_grad/Reshapegradients/loss_grad/Shape*

Tmultiples0*
T0
E
gradients/loss_grad/Shape_1ShapeSquare*
out_type0*
T0
D
gradients/loss_grad/Shape_2Const*
valueB *
dtype0
G
gradients/loss_grad/ConstConst*
valueB: *
dtype0
~
gradients/loss_grad/ProdProdgradients/loss_grad/Shape_1gradients/loss_grad/Const*
T0*

Tidx0*
	keep_dims( 
I
gradients/loss_grad/Const_1Const*
valueB: *
dtype0
?
gradients/loss_grad/Prod_1Prodgradients/loss_grad/Shape_2gradients/loss_grad/Const_1*

Tidx0*
	keep_dims( *
T0
G
gradients/loss_grad/Maximum/yConst*
value	B :*
dtype0
j
gradients/loss_grad/MaximumMaximumgradients/loss_grad/Prod_1gradients/loss_grad/Maximum/y*
T0
h
gradients/loss_grad/floordivFloorDivgradients/loss_grad/Prodgradients/loss_grad/Maximum*
T0
f
gradients/loss_grad/CastCastgradients/loss_grad/floordiv*

SrcT0*
Truncate( *

DstT0
c
gradients/loss_grad/truedivRealDivgradients/loss_grad/Tilegradients/loss_grad/Cast*
T0
f
gradients/Square_grad/ConstConst^gradients/loss_grad/truediv*
valueB
 *   @*
dtype0
K
gradients/Square_grad/MulMulsubgradients/Square_grad/Const*
T0
c
gradients/Square_grad/Mul_1Mulgradients/loss_grad/truedivgradients/Square_grad/Mul*
T0
B
gradients/sub_grad/ShapeShapeoutput*
T0*
out_type0
D
gradients/sub_grad/Shape_1Shapetarget*
T0*
out_type0
?
(gradients/sub_grad/BroadcastGradientArgsBroadcastGradientArgsgradients/sub_grad/Shapegradients/sub_grad/Shape_1*
T0
?
gradients/sub_grad/SumSumgradients/Square_grad/Mul_1(gradients/sub_grad/BroadcastGradientArgs*
T0*

Tidx0*
	keep_dims( 
n
gradients/sub_grad/ReshapeReshapegradients/sub_grad/Sumgradients/sub_grad/Shape*
T0*
Tshape0
C
gradients/sub_grad/NegNeggradients/Square_grad/Mul_1*
T0
?
gradients/sub_grad/Sum_1Sumgradients/sub_grad/Neg*gradients/sub_grad/BroadcastGradientArgs:1*
T0*

Tidx0*
	keep_dims( 
t
gradients/sub_grad/Reshape_1Reshapegradients/sub_grad/Sum_1gradients/sub_grad/Shape_1*
T0*
Tshape0
g
#gradients/sub_grad/tuple/group_depsNoOp^gradients/sub_grad/Reshape^gradients/sub_grad/Reshape_1
?
+gradients/sub_grad/tuple/control_dependencyIdentitygradients/sub_grad/Reshape$^gradients/sub_grad/tuple/group_deps*
T0*-
_class#
!loc:@gradients/sub_grad/Reshape
?
-gradients/sub_grad/tuple/control_dependency_1Identitygradients/sub_grad/Reshape_1$^gradients/sub_grad/tuple/group_deps*
T0*/
_class%
#!loc:@gradients/sub_grad/Reshape_1
?
(gradients/dense/BiasAdd_grad/BiasAddGradBiasAddGrad+gradients/sub_grad/tuple/control_dependency*
T0*
data_formatNHWC
?
-gradients/dense/BiasAdd_grad/tuple/group_depsNoOp)^gradients/dense/BiasAdd_grad/BiasAddGrad,^gradients/sub_grad/tuple/control_dependency
?
5gradients/dense/BiasAdd_grad/tuple/control_dependencyIdentity+gradients/sub_grad/tuple/control_dependency.^gradients/dense/BiasAdd_grad/tuple/group_deps*
T0*-
_class#
!loc:@gradients/sub_grad/Reshape
?
7gradients/dense/BiasAdd_grad/tuple/control_dependency_1Identity(gradients/dense/BiasAdd_grad/BiasAddGrad.^gradients/dense/BiasAdd_grad/tuple/group_deps*
T0*;
_class1
/-loc:@gradients/dense/BiasAdd_grad/BiasAddGrad
^
$gradients/dense/Tensordot_grad/ShapeShapedense/Tensordot/MatMul*
T0*
out_type0
?
&gradients/dense/Tensordot_grad/ReshapeReshape5gradients/dense/BiasAdd_grad/tuple/control_dependency$gradients/dense/Tensordot_grad/Shape*
T0*
Tshape0
?
,gradients/dense/Tensordot/MatMul_grad/MatMulMatMul&gradients/dense/Tensordot_grad/Reshapedense/kernel/read*
T0*
transpose_a( *
transpose_b(
?
.gradients/dense/Tensordot/MatMul_grad/MatMul_1MatMuldense/Tensordot/Reshape&gradients/dense/Tensordot_grad/Reshape*
T0*
transpose_a(*
transpose_b( 
?
6gradients/dense/Tensordot/MatMul_grad/tuple/group_depsNoOp-^gradients/dense/Tensordot/MatMul_grad/MatMul/^gradients/dense/Tensordot/MatMul_grad/MatMul_1
?
>gradients/dense/Tensordot/MatMul_grad/tuple/control_dependencyIdentity,gradients/dense/Tensordot/MatMul_grad/MatMul7^gradients/dense/Tensordot/MatMul_grad/tuple/group_deps*
T0*?
_class5
31loc:@gradients/dense/Tensordot/MatMul_grad/MatMul
?
@gradients/dense/Tensordot/MatMul_grad/tuple/control_dependency_1Identity.gradients/dense/Tensordot/MatMul_grad/MatMul_17^gradients/dense/Tensordot/MatMul_grad/tuple/group_deps*
T0*A
_class7
53loc:@gradients/dense/Tensordot/MatMul_grad/MatMul_1
@
train/learning_rateConst*
valueB
 *
?#<*
dtype0
?
.train/update_dense/kernel/ApplyGradientDescentApplyGradientDescentdense/kerneltrain/learning_rate@gradients/dense/Tensordot/MatMul_grad/tuple/control_dependency_1*
use_locking( *
T0*
_class
loc:@dense/kernel
?
,train/update_dense/bias/ApplyGradientDescentApplyGradientDescent
dense/biastrain/learning_rate7gradients/dense/BiasAdd_grad/tuple/control_dependency_1*
use_locking( *
T0*
_class
loc:@dense/bias
m
trainNoOp-^train/update_dense/bias/ApplyGradientDescent/^train/update_dense/kernel/ApplyGradientDescent
6
initNoOp^dense/bias/Assign^dense/kernel/Assign
A
save/filename/inputConst*
valueB Bmodel*
dtype0
V
save/filenamePlaceholderWithDefaultsave/filename/input*
dtype0*
shape: 
M

save/ConstPlaceholderWithDefaultsave/filename*
shape: *
dtype0
]
save/SaveV2/tensor_namesConst*-
value$B"B
dense/biasBdense/kernel*
dtype0
K
save/SaveV2/shape_and_slicesConst*
valueBB B *
dtype0
?
save/SaveV2SaveV2
save/Constsave/SaveV2/tensor_namessave/SaveV2/shape_and_slices
dense/biasdense/kernel*
dtypes
2
e
save/control_dependencyIdentity
save/Const^save/SaveV2*
T0*
_class
loc:@save/Const
o
save/RestoreV2/tensor_namesConst"/device:CPU:0*-
value$B"B
dense/biasBdense/kernel*
dtype0
]
save/RestoreV2/shape_and_slicesConst"/device:CPU:0*
valueBB B *
dtype0
?
save/RestoreV2	RestoreV2
save/Constsave/RestoreV2/tensor_namessave/RestoreV2/shape_and_slices"/device:CPU:0*
dtypes
2
?
save/AssignAssign
dense/biassave/RestoreV2*
use_locking(*
T0*
_class
loc:@dense/bias*
validate_shape(
?
save/Assign_1Assigndense/kernelsave/RestoreV2:1*
validate_shape(*
use_locking(*
T0*
_class
loc:@dense/kernel
6
save/restore_allNoOp^save/Assign^save/Assign_1"?