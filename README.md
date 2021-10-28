# VU_BC_BlockChain

## Turinys
- [Užduotis](#užduotis)
- [Programos paleidimas](#programos-paleidimas)
- [Blokų grandinės](#blockchain)
  - [Veikimo principas](#veikimo-principas)
  - [Vartotojų generavimas](#user-generation)
  - [Transakcijų generativmas](#transaction-generation)
  - [Blokų generavimas](#block-generation)
 
## Užduotis
Sukurkite "centralizuotą" blokų grandinę (blockchain'ą) ir susimuliuokite blokų grandinės veikimą kuo natūralesnėmis sąlygomis. 

1. Sugeneruoti ~1000 tinklo vartotojų (aka user'ių), kurie turėtų bent tris atributus:
   - vardą.
   - viešąjį hash raktą (public_key).
   - tam tikros valiutos atsitiktinį balansą (pvz., nuo 100 iki 1000000 valiutos vienetų).
2. Sugeneruoti ~10000 naujų, į jokį bloką dar neįdėtų, transakcijų pool'ą, o transakcijos turėtų bent šiuos atributus:
   - transakcijos ID (kitų transakcijos laukų hash'as),
   - siuntėjas (jo viešasis raktas)
   - gavėjas (jo viešasis raktas)
   - suma
3. Iš transakcijų pool'o atsitiktinai pasirinkti 100-ą transakcijų, kurias bandysime įdėti į naują bloką.
4. Realizuokite naujų blokų kasimo (angl. mining) Proof-of-Work (PoW) tipo procesą, kurio tikslas yra surasti naujam blokui hash'ą, tenkinantį
Difficulty Target reikalavimą, t.y., hash'o pradžioje esančių nulių tam tikrą skaičių.
5. Suradus tokį naujo bloko hash'ą:
   - į naują bloką priskirtas transakcijas ištrinkite iš transakcijų pool'o.
   - "įvykdykite" transakcijas.
   - naują bloką pridėkite prie blockchain grandinės.
6. Kartoti 3-5 žingsnius tol, kol yra laisvų transakcijų.
---

## Programos paleidimas
Programa paleidžiama komandinėje eilutėje naudojant `./main`.
```shell
./main
```
Paleidus programą `./main`, galima pasirinkti ar:
- Naudoti jau nustatytas reikšmes
```shell
> Use default values? (y/n): y
User count = 1000, Transaction count = 10000, Transactions in block = 100
```
- Įvesti reikšmes
```shell
> Use default values? (y/n): n
User count (>1): 2
Transaction count (>0): 1
Transactions in block: 1
```
---

## Blockchain
### Veikimo principas
Sugeneruojami vartotojai, transakcijos ir paleidžiamas while loop, kurio metu:
- Sugeneruojamas naujas blokas.
- Į bloką įdedamos transakcijos.
- Blokas yra iškasamas.
  - Kasami 5 blokai lygiagrečiai, grąžinamas greičiausiai "iškastas" blokas.
- Bloko transakcijos pašalinamos iš bendro pool'o.
- Kiekviena transakcija yra įvykdoma.
- Blokas atspausdinamas į failą.
---
### User generation
Sugeneruojami vartotojai, kuriems priskiramas tam tikras valiutos balansas (nuo 100 iki 1000000). Visi vartotojai yra atspausdinami `users_start.txt` ir `users_end.txt` failuose.
```shell
Name: User-1
Public key: 7fdeb5feb7f7fde6fdfde7aa3ff4ffca57e81c9d96b23f3550fa7e3f814c2dcb
Current balance: 555912
--------------------------------------------------
Name: User-2
Public_key: ffd4d59dfd7cf3be6d9d7efeb676f7bb5f7b43afff4f4e8dce1e6e2b10fb590f
Current_balance: 404062
--------------------------------------------------
```
---
### Transaction generation
Sugeneruojamos transakcijos, kurioms priskirama tam tikras valiutos kiekis pagal sountėjo balansą. Visos transakcijos sudedamos į bendrą "pool'ą". Visos transakcijos yra atspausdinami `all_transactions.txt` faile.
```shell
TANSACTION ID: f4fcdcfedda6bae6a7bfeb9cbef595fbb8eb6767b1a713a7897a174d7f552705
SENDERS_PUBLIC_KEY: d573f55d7fddf3edbfdafef4f9aa4ffa49db70d36201fa543979ae22c4af3275
RECEIVERS_PUBLIC_KEY: faffd926fbefe4fea3fbaff4f13fffabb21eb817f336061b571a9f91dbe3adb1
AMOUNT: 16929
--------------------------------------------------
TANSACTION ID: 8ab7bf55fab3a5bffbfdebfff8ff28f7e19379d3bc03469c8c12f748323dd3ac
SENDERS_PUBLIC_KEY: c5d3b7b67fdff7fefa76da5a6f955dfbadeeec9f90cbc4eddebbfc11ee52943b
RECEIVERS_PUBLIC_KEY: fcd7fbfef67ef9b6e7bffefed7e7d4fb25d6a4ef8663488595a663858e560b57
AMOUNT: 103717
--------------------------------------------------
```
---
### Block generation
Sugeneruojami blokų grandinės blokai. Visi blokai yra atspausdinami `block-(1..n).txt` failuose.
```shell
Block: 1
--------------------------------------------------
Block hash: 07bf76ed42bfb7bdfe7d7daf6feb5ec7f162a5f382645c7460670a102396c354
Previous block hash: 0000000000000000000000000000000000000000000000000000000000000000
Timestamp: 2021-10-14 17:55:34
Transaction count: 100
Difficulty: 1
Merkle root hash: 6f9dff3dcc37d4fcaafeeedef5ceedfe11b30b612fa74ff105ae2cbb303a333b
Version: 0.1
Nonce: 2
Transaction volume: 12162113

TRANSACTIONS
--------------------------------------------------
Transaction ID: f4fcdcfedda6bae6a7bfeb9cbef595fbb8eb6767b1a713a7897a174d7f552705
Sender public key: d573f55d7fddf3edbfdafef4f9aa4ffa49db70d36201fa543979ae22c4af3275
Receiver public key: faffd926fbefe4fea3fbaff4f13fffabb21eb817f336061b571a9f91dbe3adb1
Amount: 16929
--------------------------------------------------
Transaction ID: 8ab7bf55fab3a5bffbfdebfff8ff28f7e19379d3bc03469c8c12f748323dd3ac
Sender public key: c5d3b7b67fdff7fefa76da5a6f955dfbadeeec9f90cbc4eddebbfc11ee52943b
Receiver public key: fcd7fbfef67ef9b6e7bffefed7e7d4fb25d6a4ef8663488595a663858e560b57
Amount: 103717
--------------------------------------------------
```
