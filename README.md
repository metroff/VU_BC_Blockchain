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
Sugeneruojami vartotojai, kuriems atsitiktinai yra priskiriamas valiutos kiekis (100 - 1000000).

Sugeneruojamos UTXO tipo transakcijos atsitiktinai parinktiems vartotojams.

Bloko generavimas (kasimas):
- Sugeneruojamas naujas blokas.
- Į bloką įdedamos transakcijos.
- Blokas yra iškasamas.
  - Kasami 5 blokai lygiagrečiai, grąžinamas greičiausiai "iškastas" blokas.
```
Mining block: 1
Nonce limit: 100000, 1E 1D 1B 1C 1A
```
- Bloko transakcijos pašalinamos iš bendro pool'o.
- Kiekviena transakcija yra įvykdoma.
- Blokas atspausdinamas į failą.

Transakcijos paremtos UTXO modeliu, t.y. vienos transakcijos įvestis yra kitos transakcijos neišleista (unspent) išvestis. Vartotojo balansas - neišleistų išvesčių suma.

---
### User generation
Sugeneruojami vartotojai, kuriems priskiramas tam tikras valiutos balansas (nuo 100 iki 1000000). Visi vartotojai yra atspausdinami `users_start.txt` ir `users_end.txt` failuose.
```shell
Name: User-1
Public key: 3d57d75efaebb8efdf3fdd9ef59e97bb6e3b9eabb6f4e048c6030c5ac419e54e
Current balance: 129021
--------------------------------------------------
Name: User-2
Public key: fddfcf7feff74fef53e3bffdaf2f7637b348104b6257521e9ede7fa0cddf4951
Current balance: 131561
--------------------------------------------------
```
---
### Transaction generation
Sugeneruojamos transakcijos, kurioms priskirama tam tikras valiutos kiekis pagal sountėjo balansą (neišleistų išvesčių sumą). Transakcija susidaro iš įvesčių bei išvesčių, kiekviena iš jų nurodo valiutos kiekį bei vartotojo viešą raktą. Visos transakcijos sudedamos į bendrą "pool'ą" bei atspausdinamos `all_transactions.txt` faile.
```shell
Transaction ID: 7df073ae7eb2debe1a6bc6fe77cf97bb2651f3aff2dec08d444a972b9ffa9ae7
Status: Unconfirmed
Total input: 253845
Total output: 253845
INPUTS
--------------------------------------------------
Index: 1
Adress: a6e5dffcfbf7edffaf507fbea9be3ff395cccea34262772ef4f326c88887f19c
Value: 253845
--------------------------------------------------
OUTPUTS
--------------------------------------------------
Index: 0
Adress: fb9fedbdffff7de5bfb7d7777d7febc7799527a3c73420a88898ba9894f4b4e8
Value: 151324
--------------------------------------------------
Index: 1
Adress: a6e5dffcfbf7edffaf507fbea9be3ff395cccea34262772ef4f326c88887f19c
Value: 102521
--------------------------------------------------


Transaction ID: e7befff6fae723b22f97edfc59dfffbafd525d42b0bcd983f70e7df2aebc8d1f
Status: Unconfirmed
Total input: 99585
Total output: 99585
INPUTS
--------------------------------------------------
Index: 1
Adress: a986dbedffbd7bf6e75dfdfcfe7f39eb5d911ce77a74aa115fe7d9985f0b35f1
Value: 14047
--------------------------------------------------
Index: 0
Adress: a986dbedffbd7bf6e75dfdfcfe7f39eb5d911ce77a74aa115fe7d9985f0b35f1
Value: 85538
--------------------------------------------------
OUTPUTS
--------------------------------------------------
Index: 0
Adress: b1fbfeebe7b55fbfec76bbf3ff277f7f51070ddba3942a0ec9c9c768c3102716
Value: 81358
--------------------------------------------------
Index: 1
Adress: a986dbedffbd7bf6e75dfdfcfe7f39eb5d911ce77a74aa115fe7d9985f0b35f1
Value: 18227
--------------------------------------------------
```
---
### Block generation
Sugeneruojami blokų grandinės blokai. Visi blokai yra atspausdinami `block-(1..n).txt` failuose.
```shell
Block: 1
--------------------------------------------------
Block hash: 07fbd3bb52b5fefbffe9fd7bc1e9abff5ee5a923daa727186732fa506368b7e8
Previous block hash: 0000000000000000000000000000000000000000000000000000000000000000
Timestamp: 2021-11-04 21:16:08
Transaction count: 100
Difficulty: 1
Merkle root hash: fdef1eddfffab7766f9f985efbfc5fdbe0c7708fe83a0e2551a93c03109d0a7f
Version: 0.1
Nonce: 30
Transaction volume: 28153436

TRANSACTIONS
--------------------------------------------------
Transaction ID: f967f9fafdeffdebefc4f1be3ffedfbb22bc8bc30076f2320e761e9489d717d4
Status: Confirmed
Total input: 144383
Total output: 144383
INPUTS
--------------------------------------------------
Index: 1
Adress: 6f3f27feff67febefe8cefaedd14dbdb420f274f153ceb2daffda22dab2a7b4f
Value: 144383
--------------------------------------------------
OUTPUTS
--------------------------------------------------
Index: 0
Adress: e79ffbfdffd3cffefbdf99fcfffefe7e67c790f85ef168f96c5136d0a8b6c2db
Value: 2285
--------------------------------------------------
Index: 1
Adress: 6f3f27feff67febefe8cefaedd14dbdb420f274f153ceb2daffda22dab2a7b4f
Value: 142098
--------------------------------------------------
```
