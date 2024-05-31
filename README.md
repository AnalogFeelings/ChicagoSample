# ChicagoCRT Sample

[![GitHub issues](https://img.shields.io/github/issues/analogfeelings/chicagosample?style=flat-square&logo=github&label=Issues)](https://github.com/AnalogFeelings/chicagosample/issues)
[![GitHub pull requests](https://img.shields.io/github/issues-pr/analogfeelings/chicagosample?label=Pull%20Requests&style=flat-square&logo=github)](https://github.com/AnalogFeelings/chicagosample/pulls)
[![GitHub](https://img.shields.io/github/license/analogfeelings/chicagosample?label=License&style=flat-square&logo=opensourceinitiative&logoColor=white)](https://github.com/AnalogFeelings/chicagosample/blob/master/LICENSE)
[![GitHub commit activity (branch)](https://img.shields.io/github/commit-activity/m/analogfeelings/chicagosample/master?label=Commit%20Activity&style=flat-square&logo=github)](https://github.com/AnalogFeelings/chicagosample/graphs/commit-activity)
[![GitHub Repo stars](https://img.shields.io/github/stars/analogfeelings/chicagosample?label=Stargazers&style=flat-square&logo=github)](https://github.com/AnalogFeelings/chicagosample/stargazers)
[![Mastodon Follow](https://img.shields.io/mastodon/follow/109309123442839534?domain=https%3A%2F%2Ftech.lgbt%2F&style=flat-square&logo=mastodon&logoColor=white&label=Follow%20Me!&color=6364ff)](https://tech.lgbt/@analog_feelings)

This is a sample project for [ChicagoCRT](https://github.com/AnalogFeelings/ChicagoCRT), using the raw Win32 API on C17 with MSVC.

## :framed_picture: Screenshots

Windows 95 (on 86box)  
- **CPU**: Intel Pentium 75MHz
- **Motherboard**: ASUS P/I-P55T2P4
- **Memory**: 8MB
- **GPU (2D)**: S3 ViRGE/DX (375)
- **GPU (3D)**: 3dfx Voodoo
- **SPU**: SoundBlaster 16

![win95](Screenshots/Windows95.png)

Windows 11 (my PC)  
- **CPU**: AMD Ryzen 5 3600
- **Motherboard**: AORUS B450 ELITE V2
- **Memory**: 16GB DDR4
- **GPU (3D)**: RTX 2060

![win11](Screenshots/Windows11.png)

## :toolbox: Build instructions

Requires Visual Studio 2022, with the C++ workload installed and the Windows SDK.

Clone [ChicagoCRT](https://github.com/AnalogFeelings/ChicagoCRT), build it, and then copy the output `ChicagoCRT.lib` to a new `Libraries` folder on the root.  
Replace `Source/Include/ChicagoCRT.h` with an updated version from the repository if needed.

Building can then be done as with any standard C++ project, and the output will be found on the `Debug` or `Release` folder.

## :sparkles: Bonus

This repository includes a C# script to patch the executable automatically!  
You can find it in the Scripts subfolder at the root of the repository.

# :balance_scale: License

This software is licensed under the terms of the MIT license.  
You can read the terms [here](LICENSE).
