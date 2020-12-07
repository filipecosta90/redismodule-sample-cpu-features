# redismodule-sample-cpu-features
A cross platform Redis Module that warns and uses the optimized functions based on instruction set extensions available and or microarchitecture.
If you can use SSE, SSE2, SSE3, SSSE3, SSE4.1, SSE4.2, SSE4a, SSE5, AVX, AVX2, AVX-512 and you're not taking advantage of it you'll be warned that these are available on your machine and could speed up CPU computations.

### Example of unoptimized build/runtime

```
make 
```

```
$ redis-server --loadmodule ./cpu_features.so
232641:C 07 Dec 2020 01:16:55.139 # oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo
232641:C 07 Dec 2020 01:16:55.139 # Redis version=255.255.255, bits=64, commit=92ec5925, modified=1, pid=232641, just started
232641:C 07 Dec 2020 01:16:55.139 # Configuration loaded
232641:M 07 Dec 2020 01:16:55.142 * Increased maximum number of open files to 10032 (it was originally set to 1024).
232641:M 07 Dec 2020 01:16:55.142 * monotonic clock: POSIX clock_gettime
                _._                                                  
           _.-``__ ''-._                                             
      _.-``    `.  `_.  ''-._           Redis 255.255.255 (92ec5925/1) 64 bit
  .-`` .-```.  ```\/    _.,_ ''-._                                   
 (    '      ,       .-`  | `,    )     Running in standalone mode
 |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379
 |    `-._   `._    /     _.-'    |     PID: 232641
  `-._    `-._  `-./  _.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |           http://redis.io        
  `-._    `-._`-.__.-'_.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |                                  
  `-._    `-._`-.__.-'_.-'    _.-'                                   
      `-._    `-.__.-'    _.-'                                       
          `-._        _.-'                                           
              `-.__.-'                                               

232641:M 07 Dec 2020 01:16:55.143 # Server initialized
232641:M 07 Dec 2020 01:16:55.143 # WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.
232641:M 07 Dec 2020 01:16:55.144 # <sample_cpu_features> The module wasn't compiled to use AVX2 instructions, but these are available on your machine and could speed up CPU computations.
232641:M 07 Dec 2020 01:16:55.144 # <sample_cpu_features> The module wasn't compiled to use AVX instructions, but these are available on your machine and could speed up CPU computations.
232641:M 07 Dec 2020 01:16:55.144 * Module 'sample_cpu_features' loaded from ./cpu_features.so
232641:M 07 Dec 2020 01:16:55.144 * Ready to accept connections
```

Please notice:
```
232641:M 07 Dec 2020 01:16:55.144 # <sample_cpu_features> The module wasn't compiled to use AVX2 instructions, but these are available on your machine and could speed up CPU computations.
232641:M 07 Dec 2020 01:16:55.144 # <sample_cpu_features> The module wasn't compiled to use AVX instructions, but these are available on your machine and could speed up CPU computations.
```



### Example of optimized build/runtime

```
make ARCH_NATIVE=1
```

```
$ redis-server --loadmodule ./cpu_features.so
233097:C 07 Dec 2020 01:22:44.530 # oO0OoO0OoO0Oo Redis is starting oO0OoO0OoO0Oo
233097:C 07 Dec 2020 01:22:44.530 # Redis version=255.255.255, bits=64, commit=92ec5925, modified=1, pid=233097, just started
233097:C 07 Dec 2020 01:22:44.530 # Configuration loaded
233097:M 07 Dec 2020 01:22:44.532 * Increased maximum number of open files to 10032 (it was originally set to 1024).
233097:M 07 Dec 2020 01:22:44.532 * monotonic clock: POSIX clock_gettime
                _._                                                  
           _.-``__ ''-._                                             
      _.-``    `.  `_.  ''-._           Redis 255.255.255 (92ec5925/1) 64 bit
  .-`` .-```.  ```\/    _.,_ ''-._                                   
 (    '      ,       .-`  | `,    )     Running in standalone mode
 |`-._`-...-` __...-.``-._|'` _.-'|     Port: 6379
 |    `-._   `._    /     _.-'    |     PID: 233097
  `-._    `-._  `-./  _.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |           http://redis.io        
  `-._    `-._`-.__.-'_.-'    _.-'                                   
 |`-._`-._    `-.__.-'    _.-'_.-'|                                  
 |    `-._`-._        _.-'_.-'    |                                  
  `-._    `-._`-.__.-'_.-'    _.-'                                   
      `-._    `-.__.-'    _.-'                                       
          `-._        _.-'                                           
              `-.__.-'                                               

233097:M 07 Dec 2020 01:22:44.534 # Server initialized
233097:M 07 Dec 2020 01:22:44.534 # WARNING overcommit_memory is set to 0! Background save may fail under low memory condition. To fix this issue add 'vm.overcommit_memory = 1' to /etc/sysctl.conf and then reboot or run the command 'sysctl vm.overcommit_memory=1' for this to take effect.
233097:M 07 Dec 2020 01:22:44.535 * Module 'sample_cpu_features' loaded from ./cpu_features.so
233097:M 07 Dec 2020 01:22:44.536 * Ready to accept connections
```