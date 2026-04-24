# kash
graph TD
    subgraph "RP2040-Zero"
        3V3["3.3V"]
        GND["GND"]
        GP2["GP2 (SCK)"]
        GP3["GP3 (TX)"]
        GP4["GP4 (RST)"]
        GP5["GP5 (DC)"]
        GP7["GP7 (CS)"]
        GP14["GP14 (Prev/Back)"]
        GP15["GP15 (Next)"]
    end

    subgraph "GC9A01 Display"
        VCC["VCC"]
        GND_D["GND"]
        SCL["SCL"]
        SDA["SDA"]
        RES["RES"]
        DC["DC"]
        CS["CS"]
        LED["LED (BLK)"]
    end

    subgraph "Buttons"
        B1["Next Button"]
        B2["Prev/Back Button"]
    end

    %% Display Connections
    3V3 --- VCC
    3V3 --- LED
    GND --- GND_D
    GP2 --- SCL
    GP3 --- SDA
    GP4 --- RES
    GP5 --- DC
    GP7 --- CS

    %% Button Connections
    GP15 --- B1
    B1 --- GND
    GP14 --- B2
    B2 --- GND

    style RP2040-Zero fill:#f9f,stroke:#333,stroke-width:2px
    style GC9A01 Display fill:#bbf,stroke:#333,stroke-width:2px

