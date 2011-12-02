const char * lj_expand_gpu_kernel = 
"	.version 2.3\n"
"	.target sm_20\n"
"	.address_size 64\n"
"	.global .texref pos_tex;\n"
"	.entry kernel_pair (\n"
"		.param .u64 __cudaparm_kernel_pair_x_,\n"
"		.param .u64 __cudaparm_kernel_pair_lj1,\n"
"		.param .u64 __cudaparm_kernel_pair_lj3,\n"
"		.param .s32 __cudaparm_kernel_pair_lj_types,\n"
"		.param .u64 __cudaparm_kernel_pair_sp_lj_in,\n"
"		.param .u64 __cudaparm_kernel_pair_dev_nbor,\n"
"		.param .u64 __cudaparm_kernel_pair_dev_packed,\n"
"		.param .u64 __cudaparm_kernel_pair_ans,\n"
"		.param .u64 __cudaparm_kernel_pair_engv,\n"
"		.param .s32 __cudaparm_kernel_pair_eflag,\n"
"		.param .s32 __cudaparm_kernel_pair_vflag,\n"
"		.param .s32 __cudaparm_kernel_pair_inum,\n"
"		.param .s32 __cudaparm_kernel_pair_nbor_pitch,\n"
"		.param .s32 __cudaparm_kernel_pair_t_per_atom)\n"
"	{\n"
"	.reg .u32 %r<72>;\n"
"	.reg .u64 %rd<62>;\n"
"	.reg .f32 %f<107>;\n"
"	.reg .pred %p<19>;\n"
"	.shared .align 16 .b8 __cuda___cuda_local_var_32497_33_non_const_sp_lj92[16];\n"
"	.shared .align 4 .b8 __cuda___cuda_local_var_32584_35_non_const_red_acc108[3072];\n"
"	.loc	16	88	0\n"
"$LDWbegin_kernel_pair:\n"
"	.loc	16	95	0\n"
"	ld.param.u64 	%rd1, [__cudaparm_kernel_pair_sp_lj_in];\n"
"	ldu.global.f32 	%f1, [%rd1+0];\n"
"	.loc	16	96	0\n"
"	ld.global.f32 	%f2, [%rd1+4];\n"
"	.loc	16	97	0\n"
"	ld.global.f32 	%f3, [%rd1+8];\n"
"	.loc	16	98	0\n"
"	ld.global.f32 	%f4, [%rd1+12];\n"
"	st.shared.v4.f32 	[__cuda___cuda_local_var_32497_33_non_const_sp_lj92+0], {%f1,%f2,%f3,%f4};\n"
"	.loc	16	107	0\n"
"	mov.f32 	%f5, 0f00000000;     	\n"
"	mov.f32 	%f6, %f5;\n"
"	mov.f32 	%f7, 0f00000000;     	\n"
"	mov.f32 	%f8, %f7;\n"
"	mov.f32 	%f9, 0f00000000;     	\n"
"	mov.f32 	%f10, %f9;\n"
"	mov.f32 	%f11, 0f00000000;    	\n"
"	mov.f32 	%f12, %f11;\n"
"	mov.f32 	%f13, 0f00000000;    	\n"
"	mov.f32 	%f14, %f13;\n"
"	mov.f32 	%f15, 0f00000000;    	\n"
"	mov.f32 	%f16, %f15;\n"
"	ld.param.s32 	%r1, [__cudaparm_kernel_pair_t_per_atom];\n"
"	cvt.s32.u32 	%r2, %tid.x;\n"
"	div.s32 	%r3, %r2, %r1;\n"
"	cvt.s32.u32 	%r4, %ntid.x;\n"
"	div.s32 	%r5, %r4, %r1;\n"
"	rem.s32 	%r6, %r2, %r1;\n"
"	cvt.s32.u32 	%r7, %ctaid.x;\n"
"	mul.lo.s32 	%r8, %r7, %r5;\n"
"	add.s32 	%r9, %r3, %r8;\n"
"	ld.param.s32 	%r10, [__cudaparm_kernel_pair_inum];\n"
"	setp.lt.s32 	%p1, %r9, %r10;\n"
"	@!%p1 bra 	$Lt_0_19202;\n"
"	.loc	16	113	0\n"
"	ld.param.s32 	%r11, [__cudaparm_kernel_pair_nbor_pitch];\n"
"	cvt.s64.s32 	%rd2, %r11;\n"
"	mul.wide.s32 	%rd3, %r11, 4;\n"
"	cvt.s64.s32 	%rd4, %r9;\n"
"	mul.wide.s32 	%rd5, %r9, 4;\n"
"	ld.param.u64 	%rd6, [__cudaparm_kernel_pair_dev_nbor];\n"
"	add.u64 	%rd7, %rd5, %rd6;\n"
"	add.u64 	%rd8, %rd3, %rd7;\n"
"	ld.global.s32 	%r12, [%rd8+0];\n"
"	add.u64 	%rd9, %rd3, %rd8;\n"
"	ld.param.u64 	%rd10, [__cudaparm_kernel_pair_dev_packed];\n"
"	setp.ne.u64 	%p2, %rd10, %rd6;\n"
"	@%p2 bra 	$Lt_0_19714;\n"
"	.loc	16	119	0\n"
"	cvt.s32.s64 	%r13, %rd2;\n"
"	mul.lo.s32 	%r14, %r13, %r12;\n"
"	cvt.s64.s32 	%rd11, %r14;\n"
"	mul.wide.s32 	%rd12, %r14, 4;\n"
"	add.u64 	%rd13, %rd9, %rd12;\n"
"	.loc	16	120	0\n"
"	mul.lo.s32 	%r15, %r6, %r13;\n"
"	cvt.s64.s32 	%rd14, %r15;\n"
"	mul.wide.s32 	%rd15, %r15, 4;\n"
"	add.u64 	%rd16, %rd9, %rd15;\n"
"	.loc	16	121	0\n"
"	mul.lo.s32 	%r16, %r13, %r1;\n"
"	bra.uni 	$Lt_0_19458;\n"
"$Lt_0_19714:\n"
"	.loc	16	123	0\n"
"	ld.global.s32 	%r17, [%rd9+0];\n"
"	cvt.s64.s32 	%rd17, %r17;\n"
"	mul.wide.s32 	%rd18, %r17, 4;\n"
"	add.u64 	%rd19, %rd10, %rd18;\n"
"	.loc	16	124	0\n"
"	cvt.s64.s32 	%rd20, %r12;\n"
"	mul.wide.s32 	%rd21, %r12, 4;\n"
"	add.u64 	%rd13, %rd19, %rd21;\n"
"	.loc	16	125	0\n"
"	mov.s32 	%r16, %r1;\n"
"	.loc	16	126	0\n"
"	cvt.s64.s32 	%rd22, %r6;\n"
"	mul.wide.s32 	%rd23, %r6, 4;\n"
"	add.u64 	%rd16, %rd19, %rd23;\n"
"$Lt_0_19458:\n"
"	.loc	16	129	0\n"
"	ld.global.s32 	%r18, [%rd7+0];\n"
"	mov.u32 	%r19, %r18;\n"
"	mov.s32 	%r20, 0;\n"
"	mov.u32 	%r21, %r20;\n"
"	mov.s32 	%r22, 0;\n"
"	mov.u32 	%r23, %r22;\n"
"	mov.s32 	%r24, 0;\n"
"	mov.u32 	%r25, %r24;\n"
"	tex.1d.v4.f32.s32 {%f17,%f18,%f19,%f20},[pos_tex,{%r19,%r21,%r23,%r25}];\n"
"	mov.f32 	%f21, %f17;\n"
"	mov.f32 	%f22, %f18;\n"
"	mov.f32 	%f23, %f19;\n"
"	mov.f32 	%f24, %f20;\n"
"	setp.ge.u64 	%p3, %rd16, %rd13;\n"
"	@%p3 bra 	$Lt_0_28162;\n"
"	cvt.rzi.ftz.s32.f32 	%r26, %f24;\n"
"	cvt.s64.s32 	%rd24, %r16;\n"
"	ld.param.s32 	%r27, [__cudaparm_kernel_pair_lj_types];\n"
"	mul.lo.s32 	%r28, %r27, %r26;\n"
"	ld.param.u64 	%rd25, [__cudaparm_kernel_pair_lj1];\n"
"	mov.f32 	%f25, 0f00000000;    	\n"
"	mov.f32 	%f26, 0f00000000;    	\n"
"	mov.f32 	%f27, 0f00000000;    	\n"
"	mov.f32 	%f28, 0f00000000;    	\n"
"	mov.u64 	%rd26, __cuda___cuda_local_var_32497_33_non_const_sp_lj92;\n"
"$Lt_0_20482:\n"
"	.loc	16	135	0\n"
"	ld.global.s32 	%r29, [%rd16+0];\n"
"	.loc	16	136	0\n"
"	shr.s32 	%r30, %r29, 30;\n"
"	and.b32 	%r31, %r30, 3;\n"
"	cvt.s64.s32 	%rd27, %r31;\n"
"	mul.wide.s32 	%rd28, %r31, 4;\n"
"	add.u64 	%rd29, %rd26, %rd28;\n"
"	ld.shared.f32 	%f29, [%rd29+0];\n"
"	.loc	16	139	0\n"
"	and.b32 	%r32, %r29, 1073741823;\n"
"	mov.u32 	%r33, %r32;\n"
"	mov.s32 	%r34, 0;\n"
"	mov.u32 	%r35, %r34;\n"
"	mov.s32 	%r36, 0;\n"
"	mov.u32 	%r37, %r36;\n"
"	mov.s32 	%r38, 0;\n"
"	mov.u32 	%r39, %r38;\n"
"	tex.1d.v4.f32.s32 {%f30,%f31,%f32,%f33},[pos_tex,{%r33,%r35,%r37,%r39}];\n"
"	mov.f32 	%f34, %f30;\n"
"	mov.f32 	%f35, %f31;\n"
"	mov.f32 	%f36, %f32;\n"
"	mov.f32 	%f37, %f33;\n"
"	cvt.rzi.ftz.s32.f32 	%r40, %f37;\n"
"	sub.ftz.f32 	%f38, %f22, %f35;\n"
"	sub.ftz.f32 	%f39, %f21, %f34;\n"
"	sub.ftz.f32 	%f40, %f23, %f36;\n"
"	mul.ftz.f32 	%f41, %f38, %f38;\n"
"	fma.rn.ftz.f32 	%f42, %f39, %f39, %f41;\n"
"	fma.rn.ftz.f32 	%f43, %f40, %f40, %f42;\n"
"	add.s32 	%r41, %r40, %r28;\n"
"	cvt.s64.s32 	%rd30, %r41;\n"
"	mul.wide.s32 	%rd31, %r41, 16;\n"
"	add.u64 	%rd32, %rd31, %rd25;\n"
"	ld.global.f32 	%f44, [%rd32+8];\n"
"	setp.gt.ftz.f32 	%p4, %f44, %f43;\n"
"	@!%p4 bra 	$Lt_0_21762;\n"
"	.loc	16	151	0\n"
"	sqrt.approx.ftz.f32 	%f45, %f43;\n"
"	ld.global.v4.f32 	{%f46,%f47,_,%f48}, [%rd32+0];\n"
"	sub.ftz.f32 	%f49, %f45, %f48;\n"
"	.loc	16	156	0\n"
"	mul.ftz.f32 	%f50, %f49, %f49;\n"
"	rcp.approx.ftz.f32 	%f51, %f50;\n"
"	mul.ftz.f32 	%f52, %f51, %f51;\n"
"	mul.ftz.f32 	%f53, %f51, %f52;\n"
"	div.approx.ftz.f32 	%f54, %f29, %f49;\n"
"	div.approx.ftz.f32 	%f55, %f54, %f45;\n"
"	mul.ftz.f32 	%f56, %f46, %f53;\n"
"	sub.ftz.f32 	%f57, %f56, %f47;\n"
"	mul.ftz.f32 	%f58, %f53, %f57;\n"
"	mul.ftz.f32 	%f59, %f55, %f58;\n"
"	.loc	16	158	0\n"
"	fma.rn.ftz.f32 	%f27, %f39, %f59, %f27;\n"
"	.loc	16	159	0\n"
"	fma.rn.ftz.f32 	%f26, %f38, %f59, %f26;\n"
"	.loc	16	160	0\n"
"	fma.rn.ftz.f32 	%f25, %f40, %f59, %f25;\n"
"	ld.param.s32 	%r42, [__cudaparm_kernel_pair_eflag];\n"
"	mov.u32 	%r43, 0;\n"
"	setp.le.s32 	%p5, %r42, %r43;\n"
"	@%p5 bra 	$Lt_0_21250;\n"
"	.loc	16	164	0\n"
"	ld.param.u64 	%rd33, [__cudaparm_kernel_pair_lj3];\n"
"	add.u64 	%rd34, %rd33, %rd31;\n"
"	ld.global.v4.f32 	{%f60,%f61,%f62,_}, [%rd34+0];\n"
"	mul.ftz.f32 	%f63, %f60, %f53;\n"
"	sub.ftz.f32 	%f64, %f63, %f61;\n"
"	mul.ftz.f32 	%f65, %f53, %f64;\n"
"	sub.ftz.f32 	%f66, %f65, %f62;\n"
"	fma.rn.ftz.f32 	%f28, %f29, %f66, %f28;\n"
"$Lt_0_21250:\n"
"	ld.param.s32 	%r44, [__cudaparm_kernel_pair_vflag];\n"
"	mov.u32 	%r45, 0;\n"
"	setp.le.s32 	%p6, %r44, %r45;\n"
"	@%p6 bra 	$Lt_0_21762;\n"
"	.loc	16	167	0\n"
"	mov.f32 	%f67, %f6;\n"
"	mul.ftz.f32 	%f68, %f39, %f39;\n"
"	fma.rn.ftz.f32 	%f69, %f59, %f68, %f67;\n"
"	mov.f32 	%f6, %f69;\n"
"	.loc	16	168	0\n"
"	mov.f32 	%f70, %f8;\n"
"	fma.rn.ftz.f32 	%f71, %f59, %f41, %f70;\n"
"	mov.f32 	%f8, %f71;\n"
"	.loc	16	169	0\n"
"	mov.f32 	%f72, %f10;\n"
"	mul.ftz.f32 	%f73, %f40, %f40;\n"
"	fma.rn.ftz.f32 	%f74, %f59, %f73, %f72;\n"
"	mov.f32 	%f10, %f74;\n"
"	.loc	16	170	0\n"
"	mov.f32 	%f75, %f12;\n"
"	mul.ftz.f32 	%f76, %f38, %f39;\n"
"	fma.rn.ftz.f32 	%f77, %f59, %f76, %f75;\n"
"	mov.f32 	%f12, %f77;\n"
"	.loc	16	171	0\n"
"	mov.f32 	%f78, %f14;\n"
"	mul.ftz.f32 	%f79, %f39, %f40;\n"
"	fma.rn.ftz.f32 	%f80, %f59, %f79, %f78;\n"
"	mov.f32 	%f14, %f80;\n"
"	.loc	16	172	0\n"
"	mul.ftz.f32 	%f81, %f38, %f40;\n"
"	fma.rn.ftz.f32 	%f15, %f59, %f81, %f15;\n"
"	mov.f32 	%f16, %f15;\n"
"$Lt_0_21762:\n"
"$Lt_0_20738:\n"
"	.loc	16	133	0\n"
"	mul.lo.u64 	%rd35, %rd24, 4;\n"
"	add.u64 	%rd16, %rd16, %rd35;\n"
"	setp.lt.u64 	%p7, %rd16, %rd13;\n"
"	@%p7 bra 	$Lt_0_20482;\n"
"	bra.uni 	$Lt_0_18946;\n"
"$Lt_0_28162:\n"
"	mov.f32 	%f25, 0f00000000;    	\n"
"	mov.f32 	%f26, 0f00000000;    	\n"
"	mov.f32 	%f27, 0f00000000;    	\n"
"	mov.f32 	%f28, 0f00000000;    	\n"
"	bra.uni 	$Lt_0_18946;\n"
"$Lt_0_19202:\n"
"	mov.f32 	%f25, 0f00000000;    	\n"
"	mov.f32 	%f26, 0f00000000;    	\n"
"	mov.f32 	%f27, 0f00000000;    	\n"
"	mov.f32 	%f28, 0f00000000;    	\n"
"$Lt_0_18946:\n"
"	mov.u32 	%r46, 1;\n"
"	setp.le.s32 	%p8, %r1, %r46;\n"
"	@%p8 bra 	$Lt_0_24578;\n"
"	.loc	16	183	0\n"
"	mov.u64 	%rd36, __cuda___cuda_local_var_32584_35_non_const_red_acc108;\n"
"	cvt.s64.s32 	%rd37, %r2;\n"
"	mul.wide.s32 	%rd38, %r2, 4;\n"
"	add.u64 	%rd39, %rd36, %rd38;\n"
"	mov.f32 	%f82, %f27;\n"
"	st.shared.f32 	[%rd39+0], %f82;\n"
"	.loc	16	184	0\n"
"	mov.f32 	%f83, %f26;\n"
"	st.shared.f32 	[%rd39+512], %f83;\n"
"	.loc	16	185	0\n"
"	mov.f32 	%f84, %f25;\n"
"	st.shared.f32 	[%rd39+1024], %f84;\n"
"	.loc	16	186	0\n"
"	mov.f32 	%f85, %f28;\n"
"	st.shared.f32 	[%rd39+1536], %f85;\n"
"	.loc	16	188	0\n"
"	shr.s32 	%r47, %r1, 31;\n"
"	mov.s32 	%r48, 1;\n"
"	and.b32 	%r49, %r47, %r48;\n"
"	add.s32 	%r50, %r49, %r1;\n"
"	shr.s32 	%r51, %r50, 1;\n"
"	mov.s32 	%r52, %r51;\n"
"	mov.u32 	%r53, 0;\n"
"	setp.ne.u32 	%p9, %r51, %r53;\n"
"	@!%p9 bra 	$Lt_0_23042;\n"
"$Lt_0_23554:\n"
"	setp.ge.u32 	%p10, %r6, %r52;\n"
"	@%p10 bra 	$Lt_0_23810;\n"
"	.loc	16	191	0\n"
"	add.u32 	%r54, %r2, %r52;\n"
"	cvt.u64.u32 	%rd40, %r54;\n"
"	mul.wide.u32 	%rd41, %r54, 4;\n"
"	add.u64 	%rd42, %rd36, %rd41;\n"
"	ld.shared.f32 	%f86, [%rd42+0];\n"
"	add.ftz.f32 	%f82, %f86, %f82;\n"
"	st.shared.f32 	[%rd39+0], %f82;\n"
"	ld.shared.f32 	%f87, [%rd42+512];\n"
"	add.ftz.f32 	%f83, %f87, %f83;\n"
"	st.shared.f32 	[%rd39+512], %f83;\n"
"	ld.shared.f32 	%f88, [%rd42+1024];\n"
"	add.ftz.f32 	%f84, %f88, %f84;\n"
"	st.shared.f32 	[%rd39+1024], %f84;\n"
"	ld.shared.f32 	%f89, [%rd42+1536];\n"
"	add.ftz.f32 	%f85, %f89, %f85;\n"
"	st.shared.f32 	[%rd39+1536], %f85;\n"
"$Lt_0_23810:\n"
"	.loc	16	188	0\n"
"	shr.u32 	%r52, %r52, 1;\n"
"	mov.u32 	%r55, 0;\n"
"	setp.ne.u32 	%p11, %r52, %r55;\n"
"	@%p11 bra 	$Lt_0_23554;\n"
"$Lt_0_23042:\n"
"	.loc	16	195	0\n"
"	mov.f32 	%f27, %f82;\n"
"	.loc	16	196	0\n"
"	mov.f32 	%f26, %f83;\n"
"	.loc	16	197	0\n"
"	mov.f32 	%f25, %f84;\n"
"	.loc	16	198	0\n"
"	mov.f32 	%f28, %f85;\n"
"	ld.param.s32 	%r56, [__cudaparm_kernel_pair_vflag];\n"
"	mov.u32 	%r57, 0;\n"
"	setp.le.s32 	%p12, %r56, %r57;\n"
"	@%p12 bra 	$Lt_0_24578;\n"
"	.loc	16	202	0\n"
"	mov.f32 	%f82, %f6;\n"
"	st.shared.f32 	[%rd39+0], %f82;\n"
"	mov.f32 	%f83, %f8;\n"
"	st.shared.f32 	[%rd39+512], %f83;\n"
"	mov.f32 	%f84, %f10;\n"
"	st.shared.f32 	[%rd39+1024], %f84;\n"
"	mov.f32 	%f85, %f12;\n"
"	st.shared.f32 	[%rd39+1536], %f85;\n"
"	mov.f32 	%f90, %f14;\n"
"	st.shared.f32 	[%rd39+2048], %f90;\n"
"	mov.f32 	%f91, %f16;\n"
"	st.shared.f32 	[%rd39+2560], %f91;\n"
"	.loc	16	204	0\n"
"	mov.s32 	%r58, %r51;\n"
"	@!%p9 bra 	$Lt_0_25090;\n"
"$Lt_0_25602:\n"
"	setp.ge.u32 	%p13, %r6, %r58;\n"
"	@%p13 bra 	$Lt_0_25858;\n"
"	.loc	16	207	0\n"
"	add.u32 	%r59, %r2, %r58;\n"
"	cvt.u64.u32 	%rd43, %r59;\n"
"	mul.wide.u32 	%rd44, %r59, 4;\n"
"	add.u64 	%rd45, %rd36, %rd44;\n"
"	ld.shared.f32 	%f92, [%rd45+0];\n"
"	add.ftz.f32 	%f82, %f92, %f82;\n"
"	st.shared.f32 	[%rd39+0], %f82;\n"
"	ld.shared.f32 	%f93, [%rd45+512];\n"
"	add.ftz.f32 	%f83, %f93, %f83;\n"
"	st.shared.f32 	[%rd39+512], %f83;\n"
"	ld.shared.f32 	%f94, [%rd45+1024];\n"
"	add.ftz.f32 	%f84, %f94, %f84;\n"
"	st.shared.f32 	[%rd39+1024], %f84;\n"
"	ld.shared.f32 	%f95, [%rd45+1536];\n"
"	add.ftz.f32 	%f85, %f95, %f85;\n"
"	st.shared.f32 	[%rd39+1536], %f85;\n"
"	ld.shared.f32 	%f96, [%rd45+2048];\n"
"	add.ftz.f32 	%f90, %f96, %f90;\n"
"	st.shared.f32 	[%rd39+2048], %f90;\n"
"	ld.shared.f32 	%f97, [%rd45+2560];\n"
"	add.ftz.f32 	%f91, %f97, %f91;\n"
"	st.shared.f32 	[%rd39+2560], %f91;\n"
"$Lt_0_25858:\n"
"	.loc	16	204	0\n"
"	shr.u32 	%r58, %r58, 1;\n"
"	mov.u32 	%r60, 0;\n"
"	setp.ne.u32 	%p14, %r58, %r60;\n"
"	@%p14 bra 	$Lt_0_25602;\n"
"$Lt_0_25090:\n"
"	.loc	16	212	0\n"
"	mov.f32 	%f6, %f82;\n"
"	mov.f32 	%f8, %f83;\n"
"	mov.f32 	%f10, %f84;\n"
"	mov.f32 	%f12, %f85;\n"
"	mov.f32 	%f14, %f90;\n"
"	mov.f32 	%f16, %f91;\n"
"$Lt_0_24578:\n"
"$Lt_0_22530:\n"
"	selp.s32 	%r61, 1, 0, %p1;\n"
"	mov.s32 	%r62, 0;\n"
"	set.eq.u32.s32 	%r63, %r6, %r62;\n"
"	neg.s32 	%r64, %r63;\n"
"	and.b32 	%r65, %r61, %r64;\n"
"	mov.u32 	%r66, 0;\n"
"	setp.eq.s32 	%p15, %r65, %r66;\n"
"	@%p15 bra 	$Lt_0_26626;\n"
"	.loc	16	218	0\n"
"	cvt.s64.s32 	%rd46, %r9;\n"
"	ld.param.u64 	%rd47, [__cudaparm_kernel_pair_engv];\n"
"	mul.wide.s32 	%rd48, %r9, 4;\n"
"	add.u64 	%rd49, %rd47, %rd48;\n"
"	ld.param.s32 	%r67, [__cudaparm_kernel_pair_eflag];\n"
"	mov.u32 	%r68, 0;\n"
"	setp.le.s32 	%p16, %r67, %r68;\n"
"	@%p16 bra 	$Lt_0_27138;\n"
"	.loc	16	220	0\n"
"	st.global.f32 	[%rd49+0], %f28;\n"
"	.loc	16	221	0\n"
"	cvt.s64.s32 	%rd50, %r10;\n"
"	mul.wide.s32 	%rd51, %r10, 4;\n"
"	add.u64 	%rd49, %rd49, %rd51;\n"
"$Lt_0_27138:\n"
"	ld.param.s32 	%r69, [__cudaparm_kernel_pair_vflag];\n"
"	mov.u32 	%r70, 0;\n"
"	setp.le.s32 	%p17, %r69, %r70;\n"
"	@%p17 bra 	$Lt_0_27650;\n"
"	.loc	16	225	0\n"
"	mov.f32 	%f98, %f6;\n"
"	st.global.f32 	[%rd49+0], %f98;\n"
"	.loc	16	226	0\n"
"	cvt.s64.s32 	%rd52, %r10;\n"
"	mul.wide.s32 	%rd53, %r10, 4;\n"
"	add.u64 	%rd54, %rd53, %rd49;\n"
"	.loc	16	225	0\n"
"	mov.f32 	%f99, %f8;\n"
"	st.global.f32 	[%rd54+0], %f99;\n"
"	.loc	16	226	0\n"
"	add.u64 	%rd55, %rd53, %rd54;\n"
"	.loc	16	225	0\n"
"	mov.f32 	%f100, %f10;\n"
"	st.global.f32 	[%rd55+0], %f100;\n"
"	.loc	16	226	0\n"
"	add.u64 	%rd56, %rd53, %rd55;\n"
"	.loc	16	225	0\n"
"	mov.f32 	%f101, %f12;\n"
"	st.global.f32 	[%rd56+0], %f101;\n"
"	.loc	16	226	0\n"
"	add.u64 	%rd49, %rd53, %rd56;\n"
"	.loc	16	225	0\n"
"	mov.f32 	%f102, %f14;\n"
"	st.global.f32 	[%rd49+0], %f102;\n"
"	mov.f32 	%f103, %f16;\n"
"	add.u64 	%rd57, %rd53, %rd49;\n"
"	st.global.f32 	[%rd57+0], %f103;\n"
"$Lt_0_27650:\n"
"	.loc	16	229	0\n"
"	ld.param.u64 	%rd58, [__cudaparm_kernel_pair_ans];\n"
"	mul.lo.u64 	%rd59, %rd46, 16;\n"
"	add.u64 	%rd60, %rd58, %rd59;\n"
"	mov.f32 	%f104, %f105;\n"
"	st.global.v4.f32 	[%rd60+0], {%f27,%f26,%f25,%f104};\n"
"$Lt_0_26626:\n"
"	.loc	16	231	0\n"
"	exit;\n"
"$LDWend_kernel_pair:\n"
"	}\n"
"	.entry kernel_pair_fast (\n"
"		.param .u64 __cudaparm_kernel_pair_fast_x_,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_lj1_in,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_lj3_in,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_sp_lj_in,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_dev_nbor,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_dev_packed,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_ans,\n"
"		.param .u64 __cudaparm_kernel_pair_fast_engv,\n"
"		.param .s32 __cudaparm_kernel_pair_fast_eflag,\n"
"		.param .s32 __cudaparm_kernel_pair_fast_vflag,\n"
"		.param .s32 __cudaparm_kernel_pair_fast_inum,\n"
"		.param .s32 __cudaparm_kernel_pair_fast_nbor_pitch,\n"
"		.param .s32 __cudaparm_kernel_pair_fast_t_per_atom)\n"
"	{\n"
"	.reg .u32 %r<74>;\n"
"	.reg .u64 %rd<74>;\n"
"	.reg .f32 %f<114>;\n"
"	.reg .f64 %fd<4>;\n"
"	.reg .pred %p<22>;\n"
"	.shared .align 4 .b8 __cuda___cuda_local_var_32650_33_non_const_sp_lj3268[16];\n"
"	.shared .align 16 .b8 __cuda___cuda_local_var_32648_34_non_const_lj13296[1936];\n"
"	.shared .align 16 .b8 __cuda___cuda_local_var_32649_34_non_const_lj35232[1936];\n"
"	.shared .align 4 .b8 __cuda___cuda_local_var_32742_35_non_const_red_acc7168[3072];\n"
"	.loc	16	239	0\n"
"$LDWbegin_kernel_pair_fast:\n"
"	cvt.s32.u32 	%r1, %tid.x;\n"
"	mov.u32 	%r2, 3;\n"
"	setp.gt.s32 	%p1, %r1, %r2;\n"
"	@%p1 bra 	$Lt_1_21250;\n"
"	.loc	16	249	0\n"
"	mov.u64 	%rd1, __cuda___cuda_local_var_32650_33_non_const_sp_lj3268;\n"
"	cvt.s64.s32 	%rd2, %r1;\n"
"	mul.wide.s32 	%rd3, %r1, 4;\n"
"	ld.param.u64 	%rd4, [__cudaparm_kernel_pair_fast_sp_lj_in];\n"
"	add.u64 	%rd5, %rd4, %rd3;\n"
"	ld.global.f32 	%f1, [%rd5+0];\n"
"	add.u64 	%rd6, %rd3, %rd1;\n"
"	st.shared.f32 	[%rd6+0], %f1;\n"
"$Lt_1_21250:\n"
"	mov.u64 	%rd1, __cuda___cuda_local_var_32650_33_non_const_sp_lj3268;\n"
"	mov.u32 	%r3, 120;\n"
"	setp.gt.s32 	%p2, %r1, %r3;\n"
"	@%p2 bra 	$Lt_1_21762;\n"
"	.loc	16	251	0\n"
"	mov.u64 	%rd7, __cuda___cuda_local_var_32648_34_non_const_lj13296;\n"
"	cvt.s64.s32 	%rd8, %r1;\n"
"	mul.wide.s32 	%rd9, %r1, 16;\n"
"	ld.param.u64 	%rd10, [__cudaparm_kernel_pair_fast_lj1_in];\n"
"	add.u64 	%rd11, %rd10, %rd9;\n"
"	add.u64 	%rd12, %rd9, %rd7;\n"
"	ld.global.v4.f32 	{%f2,%f3,%f4,%f5}, [%rd11+0];\n"
"	st.shared.v4.f32 	[%rd12+0], {%f2,%f3,%f4,%f5};\n"
"	ld.param.s32 	%r4, [__cudaparm_kernel_pair_fast_eflag];\n"
"	mov.u32 	%r5, 0;\n"
"	setp.le.s32 	%p3, %r4, %r5;\n"
"	@%p3 bra 	$Lt_1_22274;\n"
"	.loc	16	253	0\n"
"	mov.u64 	%rd13, __cuda___cuda_local_var_32649_34_non_const_lj35232;\n"
"	ld.param.u64 	%rd14, [__cudaparm_kernel_pair_fast_lj3_in];\n"
"	add.u64 	%rd15, %rd14, %rd9;\n"
"	add.u64 	%rd16, %rd9, %rd13;\n"
"	ld.global.v4.f32 	{%f6,%f7,%f8,%f9}, [%rd15+0];\n"
"	st.shared.v4.f32 	[%rd16+0], {%f6,%f7,%f8,%f9};\n"
"$Lt_1_22274:\n"
"	mov.u64 	%rd13, __cuda___cuda_local_var_32649_34_non_const_lj35232;\n"
"$Lt_1_21762:\n"
"	mov.u64 	%rd7, __cuda___cuda_local_var_32648_34_non_const_lj13296;\n"
"	mov.u64 	%rd13, __cuda___cuda_local_var_32649_34_non_const_lj35232;\n"
"	.loc	16	263	0\n"
"	mov.f32 	%f10, 0f00000000;    	\n"
"	mov.f32 	%f11, %f10;\n"
"	mov.f32 	%f12, 0f00000000;    	\n"
"	mov.f32 	%f13, %f12;\n"
"	mov.f32 	%f14, 0f00000000;    	\n"
"	mov.f32 	%f15, %f14;\n"
"	mov.f32 	%f16, 0f00000000;    	\n"
"	mov.f32 	%f17, %f16;\n"
"	mov.f32 	%f18, 0f00000000;    	\n"
"	mov.f32 	%f19, %f18;\n"
"	mov.f32 	%f20, 0f00000000;    	\n"
"	mov.f32 	%f21, %f20;\n"
"	.loc	16	265	0\n"
"	bar.sync 	0;\n"
"	ld.param.s32 	%r6, [__cudaparm_kernel_pair_fast_t_per_atom];\n"
"	div.s32 	%r7, %r1, %r6;\n"
"	cvt.s32.u32 	%r8, %ntid.x;\n"
"	div.s32 	%r9, %r8, %r6;\n"
"	rem.s32 	%r10, %r1, %r6;\n"
"	cvt.s32.u32 	%r11, %ctaid.x;\n"
"	mul.lo.s32 	%r12, %r11, %r9;\n"
"	add.s32 	%r13, %r7, %r12;\n"
"	ld.param.s32 	%r14, [__cudaparm_kernel_pair_fast_inum];\n"
"	setp.lt.s32 	%p4, %r13, %r14;\n"
"	@!%p4 bra 	$Lt_1_23042;\n"
"	.loc	16	271	0\n"
"	ld.param.s32 	%r15, [__cudaparm_kernel_pair_fast_nbor_pitch];\n"
"	cvt.s64.s32 	%rd17, %r15;\n"
"	mul.wide.s32 	%rd18, %r15, 4;\n"
"	cvt.s64.s32 	%rd19, %r13;\n"
"	mul.wide.s32 	%rd20, %r13, 4;\n"
"	ld.param.u64 	%rd21, [__cudaparm_kernel_pair_fast_dev_nbor];\n"
"	add.u64 	%rd22, %rd20, %rd21;\n"
"	add.u64 	%rd23, %rd18, %rd22;\n"
"	ld.global.s32 	%r16, [%rd23+0];\n"
"	add.u64 	%rd24, %rd18, %rd23;\n"
"	ld.param.u64 	%rd25, [__cudaparm_kernel_pair_fast_dev_packed];\n"
"	setp.ne.u64 	%p5, %rd25, %rd21;\n"
"	@%p5 bra 	$Lt_1_23554;\n"
"	.loc	16	277	0\n"
"	cvt.s32.s64 	%r17, %rd17;\n"
"	mul.lo.s32 	%r18, %r17, %r16;\n"
"	cvt.s64.s32 	%rd26, %r18;\n"
"	mul.wide.s32 	%rd27, %r18, 4;\n"
"	add.u64 	%rd28, %rd24, %rd27;\n"
"	.loc	16	278	0\n"
"	mul.lo.s32 	%r19, %r10, %r17;\n"
"	cvt.s64.s32 	%rd29, %r19;\n"
"	mul.wide.s32 	%rd30, %r19, 4;\n"
"	add.u64 	%rd31, %rd24, %rd30;\n"
"	.loc	16	279	0\n"
"	mul.lo.s32 	%r20, %r17, %r6;\n"
"	bra.uni 	$Lt_1_23298;\n"
"$Lt_1_23554:\n"
"	.loc	16	281	0\n"
"	ld.global.s32 	%r21, [%rd24+0];\n"
"	cvt.s64.s32 	%rd32, %r21;\n"
"	mul.wide.s32 	%rd33, %r21, 4;\n"
"	add.u64 	%rd34, %rd25, %rd33;\n"
"	.loc	16	282	0\n"
"	cvt.s64.s32 	%rd35, %r16;\n"
"	mul.wide.s32 	%rd36, %r16, 4;\n"
"	add.u64 	%rd28, %rd34, %rd36;\n"
"	.loc	16	283	0\n"
"	mov.s32 	%r20, %r6;\n"
"	.loc	16	284	0\n"
"	cvt.s64.s32 	%rd37, %r10;\n"
"	mul.wide.s32 	%rd38, %r10, 4;\n"
"	add.u64 	%rd31, %rd34, %rd38;\n"
"$Lt_1_23298:\n"
"	.loc	16	287	0\n"
"	ld.global.s32 	%r22, [%rd22+0];\n"
"	mov.u32 	%r23, %r22;\n"
"	mov.s32 	%r24, 0;\n"
"	mov.u32 	%r25, %r24;\n"
"	mov.s32 	%r26, 0;\n"
"	mov.u32 	%r27, %r26;\n"
"	mov.s32 	%r28, 0;\n"
"	mov.u32 	%r29, %r28;\n"
"	tex.1d.v4.f32.s32 {%f22,%f23,%f24,%f25},[pos_tex,{%r23,%r25,%r27,%r29}];\n"
"	mov.f32 	%f26, %f22;\n"
"	mov.f32 	%f27, %f23;\n"
"	mov.f32 	%f28, %f24;\n"
"	mov.f32 	%f29, %f25;\n"
"	setp.ge.u64 	%p6, %rd31, %rd28;\n"
"	@%p6 bra 	$Lt_1_32002;\n"
"	cvt.rzi.ftz.s32.f32 	%r30, %f29;\n"
"	cvt.s64.s32 	%rd39, %r20;\n"
"	mul.lo.s32 	%r31, %r30, 11;\n"
"	cvt.rn.f32.s32 	%f30, %r31;\n"
"	mov.f32 	%f31, 0f00000000;    	\n"
"	mov.f32 	%f32, 0f00000000;    	\n"
"	mov.f32 	%f33, 0f00000000;    	\n"
"	mov.f32 	%f34, 0f00000000;    	\n"
"$Lt_1_24322:\n"
"	.loc	16	294	0\n"
"	ld.global.s32 	%r32, [%rd31+0];\n"
"	.loc	16	295	0\n"
"	shr.s32 	%r33, %r32, 30;\n"
"	and.b32 	%r34, %r33, 3;\n"
"	cvt.s64.s32 	%rd40, %r34;\n"
"	mul.wide.s32 	%rd41, %r34, 4;\n"
"	add.u64 	%rd42, %rd1, %rd41;\n"
"	ld.shared.f32 	%f35, [%rd42+0];\n"
"	.loc	16	298	0\n"
"	and.b32 	%r35, %r32, 1073741823;\n"
"	mov.u32 	%r36, %r35;\n"
"	mov.s32 	%r37, 0;\n"
"	mov.u32 	%r38, %r37;\n"
"	mov.s32 	%r39, 0;\n"
"	mov.u32 	%r40, %r39;\n"
"	mov.s32 	%r41, 0;\n"
"	mov.u32 	%r42, %r41;\n"
"	tex.1d.v4.f32.s32 {%f36,%f37,%f38,%f39},[pos_tex,{%r36,%r38,%r40,%r42}];\n"
"	mov.f32 	%f40, %f36;\n"
"	mov.f32 	%f41, %f37;\n"
"	mov.f32 	%f42, %f38;\n"
"	mov.f32 	%f43, %f39;\n"
"	sub.ftz.f32 	%f44, %f27, %f41;\n"
"	sub.ftz.f32 	%f45, %f26, %f40;\n"
"	sub.ftz.f32 	%f46, %f28, %f42;\n"
"	mul.ftz.f32 	%f47, %f44, %f44;\n"
"	fma.rn.ftz.f32 	%f48, %f45, %f45, %f47;\n"
"	fma.rn.ftz.f32 	%f49, %f46, %f46, %f48;\n"
"	add.ftz.f32 	%f50, %f30, %f43;\n"
"	cvt.rzi.ftz.s32.f32 	%r43, %f50;\n"
"	cvt.s64.s32 	%rd43, %r43;\n"
"	mul.wide.s32 	%rd44, %r43, 16;\n"
"	add.u64 	%rd45, %rd44, %rd7;\n"
"	ld.shared.f32 	%f51, [%rd45+8];\n"
"	setp.gt.ftz.f32 	%p7, %f51, %f49;\n"
"	@!%p7 bra 	$Lt_1_25602;\n"
"	.loc	16	309	0\n"
"	sqrt.approx.ftz.f32 	%f52, %f49;\n"
"	ld.shared.v4.f32 	{%f53,%f54,_,%f55}, [%rd45+0];\n"
"	sub.ftz.f32 	%f56, %f52, %f55;\n"
"	.loc	16	313	0\n"
"	mul.ftz.f32 	%f57, %f56, %f56;\n"
"	cvt.ftz.f64.f32 	%fd1, %f57;\n"
"	rcp.rn.f64 	%fd2, %fd1;\n"
"	cvt.rn.ftz.f32.f64 	%f58, %fd2;\n"
"	mul.ftz.f32 	%f59, %f58, %f58;\n"
"	mul.ftz.f32 	%f60, %f58, %f59;\n"
"	mul.ftz.f32 	%f61, %f53, %f60;\n"
"	sub.ftz.f32 	%f62, %f61, %f54;\n"
"	mul.ftz.f32 	%f63, %f60, %f62;\n"
"	.loc	16	314	0\n"
"	div.approx.ftz.f32 	%f64, %f35, %f56;\n"
"	div.approx.ftz.f32 	%f65, %f64, %f52;\n"
"	mul.ftz.f32 	%f66, %f63, %f65;\n"
"	.loc	16	316	0\n"
"	fma.rn.ftz.f32 	%f33, %f45, %f66, %f33;\n"
"	.loc	16	317	0\n"
"	fma.rn.ftz.f32 	%f32, %f44, %f66, %f32;\n"
"	.loc	16	318	0\n"
"	fma.rn.ftz.f32 	%f31, %f46, %f66, %f31;\n"
"	ld.param.s32 	%r44, [__cudaparm_kernel_pair_fast_eflag];\n"
"	mov.u32 	%r45, 0;\n"
"	setp.le.s32 	%p8, %r44, %r45;\n"
"	@%p8 bra 	$Lt_1_25090;\n"
"	.loc	16	321	0\n"
"	add.u64 	%rd46, %rd44, %rd13;\n"
"	ld.shared.v4.f32 	{%f67,%f68,%f69,_}, [%rd46+0];\n"
"	mul.ftz.f32 	%f70, %f67, %f60;\n"
"	sub.ftz.f32 	%f71, %f70, %f68;\n"
"	mul.ftz.f32 	%f72, %f60, %f71;\n"
"	.loc	16	322	0\n"
"	sub.ftz.f32 	%f73, %f72, %f69;\n"
"	fma.rn.ftz.f32 	%f34, %f35, %f73, %f34;\n"
"$Lt_1_25090:\n"
"	ld.param.s32 	%r46, [__cudaparm_kernel_pair_fast_vflag];\n"
"	mov.u32 	%r47, 0;\n"
"	setp.le.s32 	%p9, %r46, %r47;\n"
"	@%p9 bra 	$Lt_1_25602;\n"
"	.loc	16	325	0\n"
"	mov.f32 	%f74, %f11;\n"
"	mul.ftz.f32 	%f75, %f45, %f45;\n"
"	fma.rn.ftz.f32 	%f76, %f66, %f75, %f74;\n"
"	mov.f32 	%f11, %f76;\n"
"	.loc	16	326	0\n"
"	mov.f32 	%f77, %f13;\n"
"	fma.rn.ftz.f32 	%f78, %f66, %f47, %f77;\n"
"	mov.f32 	%f13, %f78;\n"
"	.loc	16	327	0\n"
"	mov.f32 	%f79, %f15;\n"
"	mul.ftz.f32 	%f80, %f46, %f46;\n"
"	fma.rn.ftz.f32 	%f81, %f66, %f80, %f79;\n"
"	mov.f32 	%f15, %f81;\n"
"	.loc	16	328	0\n"
"	mov.f32 	%f82, %f17;\n"
"	mul.ftz.f32 	%f83, %f44, %f45;\n"
"	fma.rn.ftz.f32 	%f84, %f66, %f83, %f82;\n"
"	mov.f32 	%f17, %f84;\n"
"	.loc	16	329	0\n"
"	mov.f32 	%f85, %f19;\n"
"	mul.ftz.f32 	%f86, %f45, %f46;\n"
"	fma.rn.ftz.f32 	%f87, %f66, %f86, %f85;\n"
"	mov.f32 	%f19, %f87;\n"
"	.loc	16	330	0\n"
"	mul.ftz.f32 	%f88, %f44, %f46;\n"
"	fma.rn.ftz.f32 	%f20, %f66, %f88, %f20;\n"
"	mov.f32 	%f21, %f20;\n"
"$Lt_1_25602:\n"
"$Lt_1_24578:\n"
"	.loc	16	292	0\n"
"	mul.lo.u64 	%rd47, %rd39, 4;\n"
"	add.u64 	%rd31, %rd31, %rd47;\n"
"	setp.lt.u64 	%p10, %rd31, %rd28;\n"
"	@%p10 bra 	$Lt_1_24322;\n"
"	bra.uni 	$Lt_1_22786;\n"
"$Lt_1_32002:\n"
"	mov.f32 	%f31, 0f00000000;    	\n"
"	mov.f32 	%f32, 0f00000000;    	\n"
"	mov.f32 	%f33, 0f00000000;    	\n"
"	mov.f32 	%f34, 0f00000000;    	\n"
"	bra.uni 	$Lt_1_22786;\n"
"$Lt_1_23042:\n"
"	mov.f32 	%f31, 0f00000000;    	\n"
"	mov.f32 	%f32, 0f00000000;    	\n"
"	mov.f32 	%f33, 0f00000000;    	\n"
"	mov.f32 	%f34, 0f00000000;    	\n"
"$Lt_1_22786:\n"
"	mov.u32 	%r48, 1;\n"
"	setp.le.s32 	%p11, %r6, %r48;\n"
"	@%p11 bra 	$Lt_1_28418;\n"
"	.loc	16	341	0\n"
"	mov.u64 	%rd48, __cuda___cuda_local_var_32742_35_non_const_red_acc7168;\n"
"	cvt.s64.s32 	%rd49, %r1;\n"
"	mul.wide.s32 	%rd50, %r1, 4;\n"
"	add.u64 	%rd51, %rd48, %rd50;\n"
"	mov.f32 	%f89, %f33;\n"
"	st.shared.f32 	[%rd51+0], %f89;\n"
"	.loc	16	342	0\n"
"	mov.f32 	%f90, %f32;\n"
"	st.shared.f32 	[%rd51+512], %f90;\n"
"	.loc	16	343	0\n"
"	mov.f32 	%f91, %f31;\n"
"	st.shared.f32 	[%rd51+1024], %f91;\n"
"	.loc	16	344	0\n"
"	mov.f32 	%f92, %f34;\n"
"	st.shared.f32 	[%rd51+1536], %f92;\n"
"	.loc	16	346	0\n"
"	shr.s32 	%r49, %r6, 31;\n"
"	mov.s32 	%r50, 1;\n"
"	and.b32 	%r51, %r49, %r50;\n"
"	add.s32 	%r52, %r51, %r6;\n"
"	shr.s32 	%r53, %r52, 1;\n"
"	mov.s32 	%r54, %r53;\n"
"	mov.u32 	%r55, 0;\n"
"	setp.ne.u32 	%p12, %r53, %r55;\n"
"	@!%p12 bra 	$Lt_1_26882;\n"
"$Lt_1_27394:\n"
"	setp.ge.u32 	%p13, %r10, %r54;\n"
"	@%p13 bra 	$Lt_1_27650;\n"
"	.loc	16	349	0\n"
"	add.u32 	%r56, %r1, %r54;\n"
"	cvt.u64.u32 	%rd52, %r56;\n"
"	mul.wide.u32 	%rd53, %r56, 4;\n"
"	add.u64 	%rd54, %rd48, %rd53;\n"
"	ld.shared.f32 	%f93, [%rd54+0];\n"
"	add.ftz.f32 	%f89, %f93, %f89;\n"
"	st.shared.f32 	[%rd51+0], %f89;\n"
"	ld.shared.f32 	%f94, [%rd54+512];\n"
"	add.ftz.f32 	%f90, %f94, %f90;\n"
"	st.shared.f32 	[%rd51+512], %f90;\n"
"	ld.shared.f32 	%f95, [%rd54+1024];\n"
"	add.ftz.f32 	%f91, %f95, %f91;\n"
"	st.shared.f32 	[%rd51+1024], %f91;\n"
"	ld.shared.f32 	%f96, [%rd54+1536];\n"
"	add.ftz.f32 	%f92, %f96, %f92;\n"
"	st.shared.f32 	[%rd51+1536], %f92;\n"
"$Lt_1_27650:\n"
"	.loc	16	346	0\n"
"	shr.u32 	%r54, %r54, 1;\n"
"	mov.u32 	%r57, 0;\n"
"	setp.ne.u32 	%p14, %r54, %r57;\n"
"	@%p14 bra 	$Lt_1_27394;\n"
"$Lt_1_26882:\n"
"	.loc	16	353	0\n"
"	mov.f32 	%f33, %f89;\n"
"	.loc	16	354	0\n"
"	mov.f32 	%f32, %f90;\n"
"	.loc	16	355	0\n"
"	mov.f32 	%f31, %f91;\n"
"	.loc	16	356	0\n"
"	mov.f32 	%f34, %f92;\n"
"	ld.param.s32 	%r58, [__cudaparm_kernel_pair_fast_vflag];\n"
"	mov.u32 	%r59, 0;\n"
"	setp.le.s32 	%p15, %r58, %r59;\n"
"	@%p15 bra 	$Lt_1_28418;\n"
"	.loc	16	360	0\n"
"	mov.f32 	%f89, %f11;\n"
"	st.shared.f32 	[%rd51+0], %f89;\n"
"	mov.f32 	%f90, %f13;\n"
"	st.shared.f32 	[%rd51+512], %f90;\n"
"	mov.f32 	%f91, %f15;\n"
"	st.shared.f32 	[%rd51+1024], %f91;\n"
"	mov.f32 	%f92, %f17;\n"
"	st.shared.f32 	[%rd51+1536], %f92;\n"
"	mov.f32 	%f97, %f19;\n"
"	st.shared.f32 	[%rd51+2048], %f97;\n"
"	mov.f32 	%f98, %f21;\n"
"	st.shared.f32 	[%rd51+2560], %f98;\n"
"	.loc	16	362	0\n"
"	mov.s32 	%r60, %r53;\n"
"	@!%p12 bra 	$Lt_1_28930;\n"
"$Lt_1_29442:\n"
"	setp.ge.u32 	%p16, %r10, %r60;\n"
"	@%p16 bra 	$Lt_1_29698;\n"
"	.loc	16	365	0\n"
"	add.u32 	%r61, %r1, %r60;\n"
"	cvt.u64.u32 	%rd55, %r61;\n"
"	mul.wide.u32 	%rd56, %r61, 4;\n"
"	add.u64 	%rd57, %rd48, %rd56;\n"
"	ld.shared.f32 	%f99, [%rd57+0];\n"
"	add.ftz.f32 	%f89, %f99, %f89;\n"
"	st.shared.f32 	[%rd51+0], %f89;\n"
"	ld.shared.f32 	%f100, [%rd57+512];\n"
"	add.ftz.f32 	%f90, %f100, %f90;\n"
"	st.shared.f32 	[%rd51+512], %f90;\n"
"	ld.shared.f32 	%f101, [%rd57+1024];\n"
"	add.ftz.f32 	%f91, %f101, %f91;\n"
"	st.shared.f32 	[%rd51+1024], %f91;\n"
"	ld.shared.f32 	%f102, [%rd57+1536];\n"
"	add.ftz.f32 	%f92, %f102, %f92;\n"
"	st.shared.f32 	[%rd51+1536], %f92;\n"
"	ld.shared.f32 	%f103, [%rd57+2048];\n"
"	add.ftz.f32 	%f97, %f103, %f97;\n"
"	st.shared.f32 	[%rd51+2048], %f97;\n"
"	ld.shared.f32 	%f104, [%rd57+2560];\n"
"	add.ftz.f32 	%f98, %f104, %f98;\n"
"	st.shared.f32 	[%rd51+2560], %f98;\n"
"$Lt_1_29698:\n"
"	.loc	16	362	0\n"
"	shr.u32 	%r60, %r60, 1;\n"
"	mov.u32 	%r62, 0;\n"
"	setp.ne.u32 	%p17, %r60, %r62;\n"
"	@%p17 bra 	$Lt_1_29442;\n"
"$Lt_1_28930:\n"
"	.loc	16	370	0\n"
"	mov.f32 	%f11, %f89;\n"
"	mov.f32 	%f13, %f90;\n"
"	mov.f32 	%f15, %f91;\n"
"	mov.f32 	%f17, %f92;\n"
"	mov.f32 	%f19, %f97;\n"
"	mov.f32 	%f21, %f98;\n"
"$Lt_1_28418:\n"
"$Lt_1_26370:\n"
"	selp.s32 	%r63, 1, 0, %p4;\n"
"	mov.s32 	%r64, 0;\n"
"	set.eq.u32.s32 	%r65, %r10, %r64;\n"
"	neg.s32 	%r66, %r65;\n"
"	and.b32 	%r67, %r63, %r66;\n"
"	mov.u32 	%r68, 0;\n"
"	setp.eq.s32 	%p18, %r67, %r68;\n"
"	@%p18 bra 	$Lt_1_30466;\n"
"	.loc	16	376	0\n"
"	cvt.s64.s32 	%rd58, %r13;\n"
"	ld.param.u64 	%rd59, [__cudaparm_kernel_pair_fast_engv];\n"
"	mul.wide.s32 	%rd60, %r13, 4;\n"
"	add.u64 	%rd61, %rd59, %rd60;\n"
"	ld.param.s32 	%r69, [__cudaparm_kernel_pair_fast_eflag];\n"
"	mov.u32 	%r70, 0;\n"
"	setp.le.s32 	%p19, %r69, %r70;\n"
"	@%p19 bra 	$Lt_1_30978;\n"
"	.loc	16	378	0\n"
"	st.global.f32 	[%rd61+0], %f34;\n"
"	.loc	16	379	0\n"
"	cvt.s64.s32 	%rd62, %r14;\n"
"	mul.wide.s32 	%rd63, %r14, 4;\n"
"	add.u64 	%rd61, %rd61, %rd63;\n"
"$Lt_1_30978:\n"
"	ld.param.s32 	%r71, [__cudaparm_kernel_pair_fast_vflag];\n"
"	mov.u32 	%r72, 0;\n"
"	setp.le.s32 	%p20, %r71, %r72;\n"
"	@%p20 bra 	$Lt_1_31490;\n"
"	.loc	16	383	0\n"
"	mov.f32 	%f105, %f11;\n"
"	st.global.f32 	[%rd61+0], %f105;\n"
"	.loc	16	384	0\n"
"	cvt.s64.s32 	%rd64, %r14;\n"
"	mul.wide.s32 	%rd65, %r14, 4;\n"
"	add.u64 	%rd66, %rd65, %rd61;\n"
"	.loc	16	383	0\n"
"	mov.f32 	%f106, %f13;\n"
"	st.global.f32 	[%rd66+0], %f106;\n"
"	.loc	16	384	0\n"
"	add.u64 	%rd67, %rd65, %rd66;\n"
"	.loc	16	383	0\n"
"	mov.f32 	%f107, %f15;\n"
"	st.global.f32 	[%rd67+0], %f107;\n"
"	.loc	16	384	0\n"
"	add.u64 	%rd68, %rd65, %rd67;\n"
"	.loc	16	383	0\n"
"	mov.f32 	%f108, %f17;\n"
"	st.global.f32 	[%rd68+0], %f108;\n"
"	.loc	16	384	0\n"
"	add.u64 	%rd61, %rd65, %rd68;\n"
"	.loc	16	383	0\n"
"	mov.f32 	%f109, %f19;\n"
"	st.global.f32 	[%rd61+0], %f109;\n"
"	mov.f32 	%f110, %f21;\n"
"	add.u64 	%rd69, %rd65, %rd61;\n"
"	st.global.f32 	[%rd69+0], %f110;\n"
"$Lt_1_31490:\n"
"	.loc	16	387	0\n"
"	ld.param.u64 	%rd70, [__cudaparm_kernel_pair_fast_ans];\n"
"	mul.lo.u64 	%rd71, %rd58, 16;\n"
"	add.u64 	%rd72, %rd70, %rd71;\n"
"	mov.f32 	%f111, %f112;\n"
"	st.global.v4.f32 	[%rd72+0], {%f33,%f32,%f31,%f111};\n"
"$Lt_1_30466:\n"
"	.loc	16	389	0\n"
"	exit;\n"
"$LDWend_kernel_pair_fast:\n"
"	}\n"
;
