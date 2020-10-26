# Lab Assignment 2 
### by Vipul B17069 and Swapnil B17104

## Problem 1
- Compile both approaches and the script using ```make```. This will generate 2 executable for approaches - ```main``` and ```main2```, and also the script executable ```script```.
- Run both the approaches using```timeout 30m ./main > filename.txt``` .
- Run the script on previously generated file using ```./script filename.txt``` to get the results.
- We have used 2 approaches to prevent deadlock and starvation. You can read more about those in the ```Analysis.pdf``` file in ```1/``` directory.

## Problem 2


## Problem 3

### Kernel compilation and installation

- Linux kernel version - 5.9.1
- After downloading and extracting the source code, I used `make gconfig` (similar to `make menuconfig` but provides GUI) to configure what to include in kernel. I removed some drivers like GPU drivers and manufacturer-specific drivers which are not required because it is running inside a VM.
- Then used `make` and `make modules_install` to compile modules, and `sudo make install` to install the compiled kernel.
- Rebooted into new kernel, and installed `linux-headers-5.9.1` package and dependencies from the Debian repository. 


### Kernel modules

- Built modules are given, but to re-compile, command ```make -C /lib/modules/\`uname -r\`/build M=$PWD``` can be used when inside the directory of the module source (`NULLdereference` directory or `panic` directory). But Linux kernel 5.9.1 headers must be installed on the system for compilation.

- Module `NULLdereference` dereferences a NULL pointer. It causes a kernel oops - an error that the kernel can recover from and the system can continue working. 

- Module `panic` calls the `panic()` function defined in the kernel libraries. This simply causes a kernel panic - which is a non-recoverable error and freezes the system. The kernel can be configured to reboot in case of a kernel panic, but by default nothing is specified, so the only option in default settings, after a kernel panic is to power off the machine. 

### Output from `sudo dmesg` when loading NULLdereference

```
[ 9847.880983] Loading custom kernel module.
[ 9847.881004] BUG: kernel NULL pointer dereference, address: 0000000000000000
[ 9847.881014] #PF: supervisor read access in kernel mode
[ 9847.881020] #PF: error_code(0x0000) - not-present page
[ 9847.881024] PGD 0 P4D 0 
[ 9847.881035] Oops: 0000 [#1] SMP PTI
[ 9847.881046] CPU: 0 PID: 86252 Comm: insmod Tainted: G           OE     5.9.1 #1
[ 9847.881052] Hardware name: innotek GmbH VirtualBox/VirtualBox, BIOS VirtualBox 12/01/2006
[ 9847.881066] RIP: 0010:init_module+0x15/0x2c [NULLdereference]
[ 9847.881074] Code: Bad RIP value.
[ 9847.881081] RSP: 0018:ffffad7506397c50 EFLAGS: 00010246
[ 9847.881087] RAX: 000000000000001d RBX: 0000000000000000 RCX: 0000000000000000
[ 9847.881093] RDX: 0000000000000000 RSI: ffff8de3dd418cc0 RDI: ffff8de3dd418cc0
[ 9847.881097] RBP: ffffad7506397c50 R08: ffff8de3dd418cc0 R09: 0000000000000004
[ 9847.881102] R10: 0000000000000000 R11: 0000000000000001 R12: ffffffffc08bd000
[ 9847.881107] R13: ffff8de3a79e0070 R14: ffffffffc08bf000 R15: 0000000000000002
[ 9847.881113] FS:  00007f607f79b540(0000) GS:ffff8de3dd400000(0000) knlGS:0000000000000000
[ 9847.881120] CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
[ 9847.881125] CR2: ffffffffc08bcfeb CR3: 00000000052d4004 CR4: 00000000000706f0
[ 9847.881140] Call Trace:
[ 9847.881160]  do_one_initcall+0x4a/0x1fa
[ 9847.881193]  ? do_init_module+0x28/0x240
[ 9847.881214]  ? kmem_cache_alloc_trace+0x17e/0x2f0
[ 9847.881225]  do_init_module+0x62/0x240
[ 9847.881234]  load_module+0x280c/0x2b40
[ 9847.881248]  __do_sys_finit_module+0xbe/0x120
[ 9847.881255]  ? __do_sys_finit_module+0xbe/0x120
[ 9847.881267]  __x64_sys_finit_module+0x1a/0x20
[ 9847.881291]  do_syscall_64+0x38/0x90
[ 9847.881302]  entry_SYSCALL_64_after_hwframe+0x44/0xa9
[ 9847.881309] RIP: 0033:0x7f607f8e089d
[ 9847.881320] Code: 00 c3 66 2e 0f 1f 84 00 00 00 00 00 90 f3 0f 1e fa 48 89 f8 48 89 f7 48 89 d6 48 89 ca 4d 89 c2 4d 89 c8 4c 8b 4c 24 08 0f 05 <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d c3 f5 0c 00 f7 d8 64 89 01 48
[ 9847.881326] RSP: 002b:00007ffc31fb00a8 EFLAGS: 00000246 ORIG_RAX: 0000000000000139
[ 9847.881334] RAX: ffffffffffffffda RBX: 000055c84dc177b0 RCX: 00007f607f8e089d
[ 9847.881339] RDX: 0000000000000000 RSI: 000055c84cb38358 RDI: 0000000000000003
[ 9847.881344] RBP: 0000000000000000 R08: 0000000000000000 R09: 00007f607f9b4260
[ 9847.881349] R10: 0000000000000003 R11: 0000000000000246 R12: 000055c84cb38358
[ 9847.881354] R13: 0000000000000000 R14: 000055c84dc17750 R15: 0000000000000000
[ 9847.881362] Modules linked in: NULLdereference(OE+) btrfs blake2b_generic xor zstd_compress raid6_pq ufs qnx4 hfsplus hfs minix ntfs msdos jfs xfs libcrc32c cpuid vboxvideo(OE) nls_iso8859_1 vmwgfx snd_intel8x0 snd_ac97_codec ac97_bus snd_pcm snd_seq_midi ttm snd_seq_midi_event intel_rapl_msr drm_kms_helper snd_rawmidi intel_rapl_common snd_seq cec crct10dif_pclmul snd_seq_device ghash_clmulni_intel fb_sys_fops aesni_intel snd_timer syscopyarea crypto_simd snd sysfillrect cryptd glue_helper sysimgblt soundcore rapl joydev input_leds video mac_hid serio_raw sch_fq_codel parport_pc ppdev lp drm parport ip_tables x_tables autofs4 hid_generic usbhid hid psmouse e1000 pata_acpi crc32_pclmul ahci libahci i2c_piix4
[ 9847.881461] CR2: 0000000000000000
[ 9847.881470] ---[ end trace 543e4fc2a480d1d6 ]---
```