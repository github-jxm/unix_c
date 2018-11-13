
a.out:     file format elf32-i386


Disassembly of section .init:

080483b8 <_init>:
 80483b8:	53                   	push   %ebx
 80483b9:	83 ec 08             	sub    $0x8,%esp
 80483bc:	e8 00 00 00 00       	call   80483c1 <_init+0x9>
 80483c1:	5b                   	pop    %ebx
 80483c2:	81 c3 33 1c 00 00    	add    $0x1c33,%ebx
 80483c8:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 80483ce:	85 c0                	test   %eax,%eax
 80483d0:	74 05                	je     80483d7 <_init+0x1f>
 80483d2:	e8 49 00 00 00       	call   8048420 <__gmon_start__@plt>
 80483d7:	e8 04 01 00 00       	call   80484e0 <frame_dummy>
 80483dc:	e8 2f 02 00 00       	call   8048610 <__do_global_ctors_aux>
 80483e1:	83 c4 08             	add    $0x8,%esp
 80483e4:	5b                   	pop    %ebx
 80483e5:	c3                   	ret    

Disassembly of section .plt:

080483f0 <add@plt-0x10>:
 80483f0:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 80483f6:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 80483fc:	00 00                	add    %al,(%eax)
	...

08048400 <add@plt>:
 8048400:	ff 25 00 a0 04 08    	jmp    *0x804a000
 8048406:	68 00 00 00 00       	push   $0x0
 804840b:	e9 e0 ff ff ff       	jmp    80483f0 <_init+0x38>

08048410 <show@plt>:
 8048410:	ff 25 04 a0 04 08    	jmp    *0x804a004
 8048416:	68 08 00 00 00       	push   $0x8
 804841b:	e9 d0 ff ff ff       	jmp    80483f0 <_init+0x38>

08048420 <__gmon_start__@plt>:
 8048420:	ff 25 08 a0 04 08    	jmp    *0x804a008
 8048426:	68 10 00 00 00       	push   $0x10
 804842b:	e9 c0 ff ff ff       	jmp    80483f0 <_init+0x38>

08048430 <__libc_start_main@plt>:
 8048430:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048436:	68 18 00 00 00       	push   $0x18
 804843b:	e9 b0 ff ff ff       	jmp    80483f0 <_init+0x38>

08048440 <sub@plt>:
 8048440:	ff 25 10 a0 04 08    	jmp    *0x804a010
 8048446:	68 20 00 00 00       	push   $0x20
 804844b:	e9 a0 ff ff ff       	jmp    80483f0 <_init+0x38>

Disassembly of section .text:

08048450 <_start>:
 8048450:	31 ed                	xor    %ebp,%ebp
 8048452:	5e                   	pop    %esi
 8048453:	89 e1                	mov    %esp,%ecx
 8048455:	83 e4 f0             	and    $0xfffffff0,%esp
 8048458:	50                   	push   %eax
 8048459:	54                   	push   %esp
 804845a:	52                   	push   %edx
 804845b:	68 00 86 04 08       	push   $0x8048600
 8048460:	68 90 85 04 08       	push   $0x8048590
 8048465:	51                   	push   %ecx
 8048466:	56                   	push   %esi
 8048467:	68 04 85 04 08       	push   $0x8048504
 804846c:	e8 bf ff ff ff       	call   8048430 <__libc_start_main@plt>
 8048471:	f4                   	hlt    
 8048472:	90                   	nop
 8048473:	90                   	nop
 8048474:	90                   	nop
 8048475:	90                   	nop
 8048476:	90                   	nop
 8048477:	90                   	nop
 8048478:	90                   	nop
 8048479:	90                   	nop
 804847a:	90                   	nop
 804847b:	90                   	nop
 804847c:	90                   	nop
 804847d:	90                   	nop
 804847e:	90                   	nop
 804847f:	90                   	nop

08048480 <__do_global_dtors_aux>:
 8048480:	55                   	push   %ebp
 8048481:	89 e5                	mov    %esp,%ebp
 8048483:	53                   	push   %ebx
 8048484:	83 ec 04             	sub    $0x4,%esp
 8048487:	80 3d 1c a0 04 08 00 	cmpb   $0x0,0x804a01c
 804848e:	75 3f                	jne    80484cf <__do_global_dtors_aux+0x4f>
 8048490:	a1 20 a0 04 08       	mov    0x804a020,%eax
 8048495:	bb 18 9f 04 08       	mov    $0x8049f18,%ebx
 804849a:	81 eb 14 9f 04 08    	sub    $0x8049f14,%ebx
 80484a0:	c1 fb 02             	sar    $0x2,%ebx
 80484a3:	83 eb 01             	sub    $0x1,%ebx
 80484a6:	39 d8                	cmp    %ebx,%eax
 80484a8:	73 1e                	jae    80484c8 <__do_global_dtors_aux+0x48>
 80484aa:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80484b0:	83 c0 01             	add    $0x1,%eax
 80484b3:	a3 20 a0 04 08       	mov    %eax,0x804a020
 80484b8:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 80484bf:	a1 20 a0 04 08       	mov    0x804a020,%eax
 80484c4:	39 d8                	cmp    %ebx,%eax
 80484c6:	72 e8                	jb     80484b0 <__do_global_dtors_aux+0x30>
 80484c8:	c6 05 1c a0 04 08 01 	movb   $0x1,0x804a01c
 80484cf:	83 c4 04             	add    $0x4,%esp
 80484d2:	5b                   	pop    %ebx
 80484d3:	5d                   	pop    %ebp
 80484d4:	c3                   	ret    
 80484d5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 80484d9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080484e0 <frame_dummy>:
 80484e0:	55                   	push   %ebp
 80484e1:	89 e5                	mov    %esp,%ebp
 80484e3:	83 ec 18             	sub    $0x18,%esp
 80484e6:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 80484eb:	85 c0                	test   %eax,%eax
 80484ed:	74 12                	je     8048501 <frame_dummy+0x21>
 80484ef:	b8 00 00 00 00       	mov    $0x0,%eax
 80484f4:	85 c0                	test   %eax,%eax
 80484f6:	74 09                	je     8048501 <frame_dummy+0x21>
 80484f8:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 80484ff:	ff d0                	call   *%eax
 8048501:	c9                   	leave  
 8048502:	c3                   	ret    
 8048503:	90                   	nop

08048504 <main>:
 8048504:	55                   	push   %ebp
 8048505:	89 e5                	mov    %esp,%ebp
 8048507:	83 e4 f0             	and    $0xfffffff0,%esp
 804850a:	83 ec 20             	sub    $0x20,%esp
 804850d:	c7 44 24 04 14 00 00 	movl   $0x14,0x4(%esp)
 8048514:	00 
 8048515:	c7 04 24 1e 00 00 00 	movl   $0x1e,(%esp)
 804851c:	e8 df fe ff ff       	call   8048400 <add@plt>
 8048521:	89 44 24 1c          	mov    %eax,0x1c(%esp)
 8048525:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048529:	89 44 24 0c          	mov    %eax,0xc(%esp)
 804852d:	c7 44 24 08 14 00 00 	movl   $0x14,0x8(%esp)
 8048534:	00 
 8048535:	c7 44 24 04 2b 00 00 	movl   $0x2b,0x4(%esp)
 804853c:	00 
 804853d:	c7 04 24 1e 00 00 00 	movl   $0x1e,(%esp)
 8048544:	e8 c7 fe ff ff       	call   8048410 <show@plt>
 8048549:	c7 44 24 04 14 00 00 	movl   $0x14,0x4(%esp)
 8048550:	00 
 8048551:	c7 04 24 1e 00 00 00 	movl   $0x1e,(%esp)
 8048558:	e8 e3 fe ff ff       	call   8048440 <sub@plt>
 804855d:	89 44 24 1c          	mov    %eax,0x1c(%esp)
 8048561:	8b 44 24 1c          	mov    0x1c(%esp),%eax
 8048565:	89 44 24 0c          	mov    %eax,0xc(%esp)
 8048569:	c7 44 24 08 14 00 00 	movl   $0x14,0x8(%esp)
 8048570:	00 
 8048571:	c7 44 24 04 2b 00 00 	movl   $0x2b,0x4(%esp)
 8048578:	00 
 8048579:	c7 04 24 1e 00 00 00 	movl   $0x1e,(%esp)
 8048580:	e8 8b fe ff ff       	call   8048410 <show@plt>
 8048585:	c9                   	leave  
 8048586:	c3                   	ret    
 8048587:	90                   	nop
 8048588:	90                   	nop
 8048589:	90                   	nop
 804858a:	90                   	nop
 804858b:	90                   	nop
 804858c:	90                   	nop
 804858d:	90                   	nop
 804858e:	90                   	nop
 804858f:	90                   	nop

08048590 <__libc_csu_init>:
 8048590:	55                   	push   %ebp
 8048591:	57                   	push   %edi
 8048592:	56                   	push   %esi
 8048593:	53                   	push   %ebx
 8048594:	e8 69 00 00 00       	call   8048602 <__i686.get_pc_thunk.bx>
 8048599:	81 c3 5b 1a 00 00    	add    $0x1a5b,%ebx
 804859f:	83 ec 1c             	sub    $0x1c,%esp
 80485a2:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 80485a6:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 80485ac:	e8 07 fe ff ff       	call   80483b8 <_init>
 80485b1:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 80485b7:	29 c7                	sub    %eax,%edi
 80485b9:	c1 ff 02             	sar    $0x2,%edi
 80485bc:	85 ff                	test   %edi,%edi
 80485be:	74 29                	je     80485e9 <__libc_csu_init+0x59>
 80485c0:	31 f6                	xor    %esi,%esi
 80485c2:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80485c8:	8b 44 24 38          	mov    0x38(%esp),%eax
 80485cc:	89 2c 24             	mov    %ebp,(%esp)
 80485cf:	89 44 24 08          	mov    %eax,0x8(%esp)
 80485d3:	8b 44 24 34          	mov    0x34(%esp),%eax
 80485d7:	89 44 24 04          	mov    %eax,0x4(%esp)
 80485db:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 80485e2:	83 c6 01             	add    $0x1,%esi
 80485e5:	39 fe                	cmp    %edi,%esi
 80485e7:	75 df                	jne    80485c8 <__libc_csu_init+0x38>
 80485e9:	83 c4 1c             	add    $0x1c,%esp
 80485ec:	5b                   	pop    %ebx
 80485ed:	5e                   	pop    %esi
 80485ee:	5f                   	pop    %edi
 80485ef:	5d                   	pop    %ebp
 80485f0:	c3                   	ret    
 80485f1:	eb 0d                	jmp    8048600 <__libc_csu_fini>
 80485f3:	90                   	nop
 80485f4:	90                   	nop
 80485f5:	90                   	nop
 80485f6:	90                   	nop
 80485f7:	90                   	nop
 80485f8:	90                   	nop
 80485f9:	90                   	nop
 80485fa:	90                   	nop
 80485fb:	90                   	nop
 80485fc:	90                   	nop
 80485fd:	90                   	nop
 80485fe:	90                   	nop
 80485ff:	90                   	nop

08048600 <__libc_csu_fini>:
 8048600:	f3 c3                	repz ret 

08048602 <__i686.get_pc_thunk.bx>:
 8048602:	8b 1c 24             	mov    (%esp),%ebx
 8048605:	c3                   	ret    
 8048606:	90                   	nop
 8048607:	90                   	nop
 8048608:	90                   	nop
 8048609:	90                   	nop
 804860a:	90                   	nop
 804860b:	90                   	nop
 804860c:	90                   	nop
 804860d:	90                   	nop
 804860e:	90                   	nop
 804860f:	90                   	nop

08048610 <__do_global_ctors_aux>:
 8048610:	55                   	push   %ebp
 8048611:	89 e5                	mov    %esp,%ebp
 8048613:	53                   	push   %ebx
 8048614:	83 ec 04             	sub    $0x4,%esp
 8048617:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 804861c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804861f:	74 13                	je     8048634 <__do_global_ctors_aux+0x24>
 8048621:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 8048626:	66 90                	xchg   %ax,%ax
 8048628:	83 eb 04             	sub    $0x4,%ebx
 804862b:	ff d0                	call   *%eax
 804862d:	8b 03                	mov    (%ebx),%eax
 804862f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048632:	75 f4                	jne    8048628 <__do_global_ctors_aux+0x18>
 8048634:	83 c4 04             	add    $0x4,%esp
 8048637:	5b                   	pop    %ebx
 8048638:	5d                   	pop    %ebp
 8048639:	c3                   	ret    
 804863a:	90                   	nop
 804863b:	90                   	nop

Disassembly of section .fini:

0804863c <_fini>:
 804863c:	53                   	push   %ebx
 804863d:	83 ec 08             	sub    $0x8,%esp
 8048640:	e8 00 00 00 00       	call   8048645 <_fini+0x9>
 8048645:	5b                   	pop    %ebx
 8048646:	81 c3 af 19 00 00    	add    $0x19af,%ebx
 804864c:	e8 2f fe ff ff       	call   8048480 <__do_global_dtors_aux>
 8048651:	83 c4 08             	add    $0x8,%esp
 8048654:	5b                   	pop    %ebx
 8048655:	c3                   	ret    
