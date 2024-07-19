# BỘ CÔNG THƯƠNG
## TRƯỜNG ĐẠI HỌC CÔNG THƯƠNG TP.HỒ CHÍ MINH
### 🙡🕮🙣

### BÀI BÁO CÁO
**Môn:** Thực hành hệ thống tìm kiếm ngăn ngừa và phát hiện xâm nhập

**Đề tài:** LAB 2

**Giảng viên:** Bùi Duy Cương

**SVTH:** Huỳnh Thanh Tâm

**MSSV:** 2033210951

**TP. Hồ Chí Minh ngày 30 tháng 5 năm 2024**

## Mục lục
1. Mô hình
   - Mô hình
   - Thiết bị
3. Thiết bị và phần mềm hỗ trợ
   - Phần mềm GNS3
   - Phần mềm VMWARE
   - 3 router
   - PC-1: Server với web server
   - PC-2: Window7 với SDM
   - PC-3: Kali Linux
4. Cấu hình Cisco IPS
    - Router 1
    - Router 2
    - Router 3
    - Kali Linux
    - Win 7
    - Server
    - Cấu hình định tuyến RIP
    - Kiểm tra kết nối giữa các PC
5. Thực hiện tấn công
    - Phát hiện và ngăn chặn tấn công Ping of death từ Kali Linux
    - Phát hiện và ngăn chặn tấn công scan port
    - Phát hiện và ngăn chặn tấn công Dos

## Mô hình
![image](https://github.com/user-attachments/assets/73fc5a2e-97ae-41ca-969a-cb6a27fa54a8)
**Thiết bị**
| Thiết bị  | Interface | Địa chỉ IPv4  | Subnet mask    | Default Gateway |
|-----------|-----------|---------------|----------------|-----------------|
| SG1       | F0/0      | 192.168.10.1  | 255.255.255.0  | N/A             |
|           | S1/0      | 192.168.15.1  | 255.255.255.0  | N/A             |
|           | F1/0      | 192.168.7.1   | 255.255.255.0  | N/A             |
| SG2       | S1/0      | 192.168.15.2  | 255.255.255.0  | N/A             |
|           | S1/1      | 192.168.20.1  | 255.255.255.0  | N/A             |
| SG3       | S1/0      | 192.168.20.2  | 255.255.255.0  | N/A             |
|           | F0/0      | 192.168.14.1  | 255.255.255.0  | N/A             |
| Kali Linux| F0/0      | 192.168.14.20 | 255.255.255.0  | 192.168.14.1    |
| Server    | F0/0      | 192.168.10.33 | 255.255.255.0  | 192.168.10.1    |
| Admin     | F0/0      | 192.168.7.21  | 255.255.255.0  | 192.168.7.1     |

## Thiết bị và phần mềm hỗ trợ
- Phần mềm GNS3
- Phần mềm VMWARE
- 3 router
- PC-1: Server với web server
- PC-2: Window7 với SDM
- PC-3: Kali Linux

## Cấu hình Cisco IPS SDM
### Cấu hình thiết bị mạng
#### Router 1
```shell
R1# configure terminal 
R1(config)# interface f0/0 
R1(config-if)# ip address 192.168.10.1 255.255.255.0 
R1(config-if)# no shutdown 
R1(config-if)# exit 
R1(config)# interface f0/1
R1(config-if)# ip address 192.168.7.1 255.255.255.0 
R1(config-if)# no shutdown 
R1(config-if)# exit 
R1(config)# interface s1/0 
R1(config-if)# ip address 192.168.15.1 255.255.255.0 
R1(config-if)# no shutdown
```
#### Router 2
```shell
R2# configure terminal 
R2(config)# interface s1/0 
R2(config-if)# ip address 192.168.15.2 255.255.255.0 
R2(config-if)# no shutdown 
R2(config-if)# exit 
R2(config)# interface s1/1 
R2(config-if)# ip address 192.168.20.1 255.255.255.0 
R2(config-if)# no shutdown
```
#### Router 3
```shell
R3# configure terminal 
R3(config)# interface s1/0 
R3(config-if)# ip address 192.168.20.2 255.255.255.0 
R3(config-if)# no shutdown 
R3(config-if)# exit 
R3(config)# interface f0/0 
R3(config-if)# ip address 192.168.14.1 255.255.255.0 
R3(config-if)# no shutdown
```
#### Kali-linux
![image](https://github.com/user-attachments/assets/53628671-f50a-4fbb-a49f-8f765a2af471)
#### Window 7
![image](https://github.com/user-attachments/assets/3263aaa8-b99c-44e0-996c-8f28a0da00c8)
#### Server 
![image](https://github.com/user-attachments/assets/93c7ad2e-ad37-4d4a-99f6-dcf8282c62ab)

### Cấu hình định tuyến RIP
#### Router 1
```shell
R1(config)# router rip
R1(config-router)# version 2
R1(config-router)# network 192.168.10.0
R1(config-router)# network 192.168.7.0
R1(config-router)# network 192.168.15.0
```
#### Router 2
```shell
R2(config)# router rip
R2(config-router)# version 2
R2(config-router)# network 192.168.15.0
R2(config-router)# network 192.168.20.0
```
#### Router 3
```shell
R3(config)# router rip
R3(config-router)# version 2
R3(config-router)# network 192.168.20.0
R3(config-router)# network 192.168.14.0
```
#### Kiểm tra kết nối giữa các máy
![image](https://github.com/user-attachments/assets/185efd38-8bda-4253-9857-33a852f37c29)
#### Cấu hình Cisco IPS
```shell
R1(config)# ip http server
R1(config)# ip http secure-server
R1(config)# ip http authentication local
R1(config)# username huynhthanhtamne privilege 15 password 123456
R1(config)# line vty 0 4
R1(config-line)# privilege level 15
R1(config-line)# login local
R1(config-line)# transport input telnet
R1(config-line)# transport input telnet ssh
R1(config-line)# exit
R1(config)# logging buffered 51200 warning
```
#### Cài đặt SDM trên Window 7
##### Tải file SDM giải nén và chạy file setup
![image](https://github.com/user-attachments/assets/8b557073-481e-4a6e-89da-95d5dbb73838)
![image](https://github.com/user-attachments/assets/91158b65-7a36-4a86-8038-e3ec59dc6f11)
![image](https://github.com/user-attachments/assets/1379ca0a-28da-4aed-9bc3-19c2a425453e)
![image](https://github.com/user-attachments/assets/cdf53240-bd8d-4f45-b617-986ee047e308)
![image](https://github.com/user-attachments/assets/94e32f7e-c34e-413c-be38-83a691794901)
## Thực hiện tấn công
### Phát hiện và ngăn chặn tấn công Ping of Death từ Kali linux
#### Attacker
![image](https://github.com/user-attachments/assets/60e17dbb-5309-44fd-94a0-214fd881e2ee)
#### Router 1
![image](https://github.com/user-attachments/assets/020de397-c8cc-46d1-aaa0-3f701b40acea)
#### Window 7
Tiến hành chặn tại Sig 2151
![image](https://github.com/user-attachments/assets/0dbe205a-60b4-4b45-ac5d-688d74d20845)
#### Kết quả 
![image](https://github.com/user-attachments/assets/650de1d5-8241-47a3-b87b-bcf4be0a508a)
### Phát hiện và ngăn chặn tấn công scan port
#### Attacker
![image](https://github.com/user-attachments/assets/aeba1f17-a204-422d-911e-84ba28a0d164)
#### Router 1
![image](https://github.com/user-attachments/assets/83a9b034-1384-439c-808b-f26e1fe3c615)
#### Window 7
Tiến hành chặn tại Sig 3042
![image](https://github.com/user-attachments/assets/6aff626c-963c-4eea-8368-341239dd5b1a)
#### Kết quả
![image](https://github.com/user-attachments/assets/b6315d58-4337-4f96-8739-7a151c049452)
### Phát hiện và ngăn chặn tấn công Dos
#### Attacker 
![image](https://github.com/user-attachments/assets/eaa8a5ca-e760-4fcf-b916-2370009c7823)
#### Router 1
![image](https://github.com/user-attachments/assets/ec18b527-15ea-430a-ab7f-2e9248ae43b8)
#### Window 7
Tiến hành chặn tại Sig 3051
![image](https://github.com/user-attachments/assets/d4d77ab0-001c-4410-b162-5fa18998ec82)
#### Kết quả
![image](https://github.com/user-attachments/assets/933a53ae-430d-41b8-bc8b-cc0a01cd5f9f)




