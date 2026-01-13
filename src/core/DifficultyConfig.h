#ifndef DIFFICULTYCONFIG_H
#define DIFFICULTYCONFIG_H

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

struct DifficultyConfig {
    int poisonPercentage;
    int trapPercentage;
    int healingPercentage;
    int powerUpPercentage;
    int trapDamage;
    int poisonDamagePerTurn;
    int healAmount;
    int monsterMistakeChance;
    int monsterStartDistance;
    double poisonCureChance;
    
    static DifficultyConfig getConfig(Difficulty diff) {
        DifficultyConfig config;
        
        switch (diff) {
            case EASY:
                config.poisonPercentage = 15;
                config.trapPercentage = 10;
                config.healingPercentage = 15;
                config.powerUpPercentage = 10;
                config.trapDamage = 15;
                config.poisonDamagePerTurn = 3;
                config.healAmount = 30;
                config.monsterMistakeChance = 40;
                config.monsterStartDistance = 5;
                config.poisonCureChance = 0.3;
                break;
                
            case MEDIUM:
                config.poisonPercentage = 25;
                config.trapPercentage = 15;
                config.healingPercentage = 10;
                config.powerUpPercentage = 5;
                config.trapDamage = 25;
                config.poisonDamagePerTurn = 5;
                config.healAmount = 25;
                config.monsterMistakeChance = 20;
                config.monsterStartDistance = 3;
                config.poisonCureChance = 0.2;
                break;
                
            case HARD:
                config.poisonPercentage = 35;
                config.trapPercentage = 25;
                config.healingPercentage = 5;
                config.powerUpPercentage = 3;
                config.trapDamage = 40;
                config.poisonDamagePerTurn = 8;
                config.healAmount = 20;
                config.monsterMistakeChance = 5;
                config.monsterStartDistance = 2;
                config.poisonCureChance = 0.1;
                break;
        }
        
        return config;
    }
};

#endif