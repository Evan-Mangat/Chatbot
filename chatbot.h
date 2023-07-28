// chatbot.h

//
// Your chatbot class goes here. Make sure it works with chatbot_driver.cpp.
//

//
// You can #include any standard C++ files, but do not use any other outside
// code (unless you write it).
// Made by: Evan Mangat - side note I hope the lines help break stuff up, the code it quite lengthy!

#include <iostream>
#include <string> // For String
#include <vector> // For Vectors
#include <cstdlib> // For Rand()
#include <algorithm> // For find()
#include <sstream> // For breaking input into Individual words.

using namespace std;

class Chatbot
{
    private:
    
    // General Variables and Vectors
    
    string chatbot_name;
    
    // Vectors------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    vector<string> broken_words; // Stores the broken up input by word.
    
    vector<string> current_topic; //Stores the current topic, is wiped after the reply is sent.
    
    vector<string> unknown_memory; // Where the chatbot stores user inputs that aren't in it's database.
    
    vector<string> learned_memory; // Where the chatbot stores the explanation attached to the original input that wasn't in the databased
    
    vector<string> favourite_pokemon;
    
    vector<string> why_is_it_your_favourite_pokemon;
    
    //Strings---------------------------------------------------------------------------------------------------------------
    
    string true_keyword = "";
    
    string previous_keyword = "";
    
    string anything_else = " What else do you want to ask me or tell me about?";
    
    string I_will_remember_that = " I will be sure to remember your opinion!";
    
    //Ints---------------------------------------------------------------------------------------------------------------
    
    int keyword_index;
    
    int greeting = 1; // By default set to 1 which is active, turned 0 once the greeting is complete.
    
    int learning_flag = 0; // Set to 0 by default. Turned on when the chatbot is trying to learn something the user is telling them.
    
    int remembering_flag = 0; // Set to 0 by default. Turned on when the chatbot is trying to remember something the user told them.
    
    int yes_or_no_flag = 0; // Set to 0 if not on, if turned to 1 diverts input through a different branch of tell() function
    
    int yes_no_response = 2; // 2 when inactive, 1 when Yes, 0 When No. Determines how Chatbot respond to Yes or No questions.
    
    // THE DATABASE------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    vector<string> Type_intro_database = {"Typing", "Type", "type", "typing"};
    vector<string> lower_case_type_database = {"normal","fire","water","grass","electric","ice","fighting","poison","ground","flying","psychic","bug","rock","ghost","dragon","dark","steel","fairy"};
    vector<string> Upper_case_type_database = {"Normal","Fire","Water","Grass","Electric","Ice","Fighting","Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel","Fairy"};
    
    vector<string> Stats = {"Stats", "stats", "STATS", "Statistics"};
    vector<string> Moves = {"Moves", "MOVES", "moves", "move"};
    
    vector<string> lower_case_stats_database = {"hp", "attack", "defense", "special_attack", "special_defense", "speed"};
    vector<string> Upper_case_stats_database = {"HP", "Attack", "Defense", "Special_Attack", "Special_Defense", "Speed"};
    vector<string> Partial_case_stats_database = {"Hp", "Atk", "Defence", "Special_attack", "Special_defense", "Spd"};
    
    vector<string> IVs = {"IVs", "IVS", "ivs", "Ivs", "iVs", "iv's", "IV'S", "ivS", "iv'S", "Iv's", "IV's"};
    vector<string> EVs = {"EVs", "EVS", "evs", "Evs", "eVs", "ev's", "EV'S", "evS", "ev'S", "Ev's", "EV's"};
    
    vector<string> Move_catagories_lower_case = {"physical","special","status"};
    vector<string> Move_catagories_Upper_case = {"Physical","Special","Status"};
    
    vector<string> User_thoughts = {"Thoughts", "thoughts", "THOUGHTS"};
    
    vector<string> Evolution_database = {"Evolve", "evolve", "EVOLUTION", "Evolution", "evolution"};
    
    vector<string> Potential_greetings = {"Hello", "hello", "hi", "yo", "Hi", "Yo", "Greetings", "greetings","Hey", "hey", "Good morning", "Morning", "afternoon", "Good Afternoon", "Good Evening", "Good evening", 
                                         "good evening", "howdy", "Heller", "Howdy", "How is it going", "Good Day", "Good day", "good day"};
    
    vector<string> Potential_yes = {"Fine", "Yes", "yes", "yeah", "Yeah", "sure", "definitely", "Definitely", "Sure", "Surely", "surely", "fine", "okay", "Okay", "exactly", "Exactly", "Right", "right", "yep", "Yep",
                                    "affirmative", "Affirmative", "Fine", "true", "True", "yea", "Yea", "indubitably", "Indubitably", "certainly", "Certainly", "positivly", "Positivly"};
                                    
    vector<string> Potential_no = {"No","no","nope","Nope","nah","Nah", "nae", "Nae"};
    
    vector<string> Potential_contradiction = {"Not", "not", "neither", "Neither", "NOT"};
    
    // Specific Response Arrays and Strings---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // For empty_responses---------------------------------------------------------------------------------------------------------------
    
    string empty_responses[4] = {"I'm sorry you seem to not want to talk?","I'm not a fan of empty responses.","I can't understand what you want if you don't talk to me","What's with the silence?"};
    
    //Initial Greetings---------------------------------------------------------------------------------------------------------------
    
    string initial_greeting_how_responses[3] = {"Hello I'm good, thank you for asking.", "Greetings I'm doing well, I appreciate you asking!", "Good to talk to you, I am doing well."};
    string initial_greeting_responses[3] = {"Hello, glad to meet you!", "Greetings and Salutations!.", "Good to talk to you."};
    
    // Super Basic Beginner Responses---------------------------------------------------------------------------------------------------------------
    
    string Beginner_intro = "Oh. Okay than well Pokemon is a very large franchise that includes trading cards, video games, phone apps, merchandise, multiple animated shows and more. I love the franchise a lot and that's why I was hired by The Pokemon Company to help people! You see";
    
    // Job Responses---------------------------------------------------------------------------------------------------------------
    
    string job_initiation[4] = {" Tell me do you know what Pokemon is?"," Are you aware of what Pokemon is?"," Have you heard of Pokemon before?"," Tell me, do you know of Pokemon?"};
    string job_response = " my job is to help people learn and understand Pokemon game mechanics! Their Stats, Types, Moves, Evolution as well as what IVs and EVs are.\nIf you don't care about Pokemon or want to talk about something else, I might be a bit of a bore conversation wise but you can still teach me things and I will try to remember them. So what do you want to talk about? Stats, Types, Moves, IVs, EVs, or maybe even teach me something I don't know!";
    
    //---------------------------------------------------------------------------------------------------------------
    //Misunderstanding for a yes_no question or the greeting.
    
    string misunderstood_greetings[3] = {"I'm not familiar with that greeting?","I've never been greeted like that before!","Wow, I've never heard that one before!"};
    string not_yes_or_no[2] = {"I'm sorry I don't quite understand your answer. Could you put it more simply?", "I apologize outside of Pokemon I'm not the sharpest tool in the shed. Could you answer my question again? This time more simply?"};
    
    // Responses when the AI learns something / is learning---------------------------------------------------------------------------------------------------------------
    
    string unknown_chat[3] = {"I'm not familiar with that. Could you explain?", "I don't understand. Could you tell me about it?", "Hmm I can't say I know what you're talking about. Could you explain to me what that is or means?"};
    string learning_responses[5] = {"Understood, I'll remember what you said!","All right, I got it! I will remember that for next time.","That's cool, I'll remember for next time!","Interesting, I will be sure to remember that!","Okay I will try to remember that!"};
    string learned_response_add_on = " If you ask me about the concept I was originally unfamiliar with again, I will tell you what you just told me.";
    string remembered_responses[1] = {"Oh I remember that, this is what you told me about it: "};
    
    //---------------------------------------------------------------------------------------------------------------
    // Reponses for when there is more than one keyword.
    
    string multiple_keywords[2] = {"Hey you seemed to have said more than one thing that caught my attention, which do you want to talk about: ","Oh I can help with two of the things you mentioned, which one would you like to talk to me about?: "};
    
    // End of Specific Scenario Responses----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------   
    
    // Beginning of pokemon-based arrays 
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    // Concept Introductions---------------------------------------------------------------------------------------------------------------
    
    string stats_intro = "In the pokemon games there are 6 stats: HP: How much damage a Pokemon can take in battle. Attack: How much damage a Pokemon does with physical moves. Defense: How well a Pokemon defends again physical attacks. Special_Attack: How much damage a Pokemon does with non-physical or 'special' moves. Special_Defense: Like Defense but for 'special_attacks'. Finally, Speed: Determines which Pokemon goes first! If you want to learn any of the stats more in-depth just ask about the particular stat!";
    
    string IVs_intro = "There are 6 IVs per Pokemon, one for each stat. IVs stands for Individual Values and each Pokemon stat has an IV from 0-31. 31 is the highest and best while 0 is the opposite. Ideally you want all 6 of them to be 31 with few exceptions. You can accomplish this many ways that differ from game to game.";
    
    string EVs_intro = "EVs or Effort Values are stat points allocated to your Pokemon when it defeats another in battle. The effort values you gain depend on the Pokemon you defeat for example defeating the Pokemon Machop grants you attack effort values. These increase the corresponding stat of your Pokemon. Make sure to defeat the right Pokemon to gain the correct effort values!";
   
    string Moves_intro = "Moves are diffferent actions a Pokemon can take in a battle. Each Pokemon can learn up to four moves at a time.\nThe moves one can learn vary from Pokemon to Pokemon.\nEach move also has a type associated with it. If a Pokemon uses an attack move with that is the same type as it, it will deal 1.5 times the damage.\nThere are 3 Catagories of move: Physical, Special and Status.\nPhysical moves are attacks that deal damage based on your Pokemons Attack stat.\nSpecial moves are attacks that deal damage based on your Pokemons Special_Attack stat.\nFinally Status moves are moves that do things that aren't attacks.\nThis varies widely from raising stats to inflicting an ailment on the opposing Pokemon.\nThere are certain exceptions to all these rules but this is a good general description of all the catagories.\nIf you would like to know more about each catagory just mention it and I will happily explain!.";
    
    string type_intro = "All Pokemon have a typing associated with them that grant them strengths and weaknesses.\nThere are 18 types: Normal, Fire, Water, Grass, Electric, Ice, Fighting, Poison, Ground, Flying, Psychic, Bug, Rock, Ghost, Dragon, Dark, Steel, and Fairy.\nEach has their own weaknesses, resistances. If hit by a type they are weak to, the Pokemon will take 2 times the normal damage.\nInversely, if you atack a Pokemon with a type they resist they will take half the normal damage.\nThese effects can stack. For example attack a Charizard with a Rock type move causes four times the damage.\nThis is because both of Charizards types, Fire and Flying, are weak to Rock.\nOn that note Pokemon can have up to two types, inheriting both those types resistances and weaknesses.\nFinally certain typings have immunities meaning moves of a certain type don't affect them.";
    
    string evolution_intro = "Most Pokemon when certain conditions are met evolve into their next form.\nThese conditions vary, some require items, some by earning experience through battle, some by friendship with the player, etc.\nWhen a Pokemon evolves they generally become stronger, gain access to new moves as well as sometimes gain a typing!";
    
    //--------------------------------------------------------------------------------------------------------------------------------------
    // Types Responses 
    // Order within the all the type arrays goes as follows: Normal, Fire, Water, Grass, Electric, Ice, Fighting, Poison, Ground, Flying, Psychic, Bug, Rock, Ghost, Dragon, Dark, Steel, Fairy
    
    string type_responses_super_array[18] = 
    {"Normal type Pokemon are very diverse. They can learn a wide variety of moves and are generally very balanced when it comes to stats.\nThey are weak to fighting types, resist nothing and are immune to ghost.",
    "Fire type Pokemon are very strong offensively and have access to powerful moves like Flamethrower and Fire Blast.\nThey are generally offensive based both Physically and Specially. They are weak to Rock, Ground and Water types and resist Bug, Grass, Fairy, Ice, Steel and Fire.", 
    "Water types are generally fairly bulky defense wise\n They have access to many powerful moves like Hydro Pump and Surf.\nThey are weak to Electric and Grass and resist Fire, Water, Ice and Steel.", 
    "Grass types are a very mixed bag. They have a wide variety of Pokemon that cover many roles.\nThey don't really have many moves that rival Surf or Flamethrower as they have a lot of good status moves.\nThey are weak to Fire, Ice, Flying, Bug and Poison and resist Grass, Electric, Ground and Water.", 
    "Electric types are generally speedy and hit hard with high Special_Attack.\nSome powerful moves they have include Thunder and Thunderbolt. They are only weak to the Ground type and resist Steel, Electric and Flying.", 
    "Ice types are generally either very defensive or very offensive\nIce beam is the most notable Ice type move because it is learned by most Water types.\nThey are weak to Rock, Fighting, Fire and Steel and only resists itself, so defensively not a good type to be.", 
    "Fighting types are generally offensive\nBrick Break and Mach Punch are two notable Fighting type moves.\n They are weak to Fairy, Flying and Psychic and resist Bug, Dark and Rock.", 
    "Poison types vary greatly due to much overlap with other types.\nNoteworthy moves include Sludge Bomb and Toxic.\nThe are weak to Ground and Psychic and resist Fighting, Poison, Bug, Grass and Fairy.", 
    "Ground types are similar to Poison types in that they overlap with other types alot.\nHowever they are generally Physical attack based Pokemon.\nThe Ground types most notable moves are Earthquake and Spikes\nThey are weak to Grass, Ice and Water, resist Poison and Rock, and they are also immune to Electric.", 
    "Flying types are generally offensive with a few notable exceptions like Skarmory\nNotable Flying type moves include Hurricane and Brave Bird.\nFlying types are weak to Electric, Ice and Rock but resist Bug, Fighting and Grass.\nIn addition they are immune to Ground", 
    "Psychic types are almost exclusively Special based. Some notable moves are Psychic and Calm Mind.\nPsychic types are weak to Bug, Ghost and Dark. An easy way to remember this is they are all common fears!\nAlso they resist Fighting and Psychic.", 
    "Bug types differ greatly and don't generally follow any trend.\nSome notable Bug type moves are X-Scissor and Sticky Web.\nBug types are weak to Fire, Flying and Rock and resist Fighting, Grass and Ground.",
    "Rock types are the opposite of Psychic types in that they are Physical both offensively and defensively.\nSome notable Rock type moves include Rock Slide and Stealth Rock.\nThey are weak to Fighting, Water, Grass, Steel and Ground.\nThey resist Fire, Flying, Normal and Poison.", 
    "Ghost types are usually a middle ground between offense and defense.\nNotable moves include Shadow Sneak and Shadow Ball.\nThey are weak to Dark and Ghost, they resist Bug and Poison and are completely immune to Normal and Fighting types.", 
    "Dragon types are some of the stongest in the game being good or great in every stat.\nNotable Dragon moves include Outrage, Draco Meteor and Dragon Claw.\n They are weak to Ice, Fairy and Dragon and resist Fire, Water, Grass and Electric.", 
    "Dark types are either very bad or offensive juggernauts.\nNotable Dark moves include Dark Pulse, Crunch and Pursuit.\nThey are weak to Bug, Fairy and Fighting, resist Dark and Ghost and are immune to Psychic.", 
    "Steel types are the best defense typing in the game.\nNotable Steel moves include Iron Head and Bullet Punch.\nThey are weak to Fire, Fighting and Ground.\nThey resist the following: Bug, Dragon, Fairy, Flying, Grass, Ice Normal, Psychic, Rock and Steel.\nAdditionally they are immune to poison.",
    "Fairy types lean towards the Special stats and are good defensively.\nNotable Fairy moves include Moonblast and Play Rough.\nThey are weak to Poison and Steel, they resist Bug, Dark and Fighting.\nFinally they are immune to Dragon which makes them quite potent defensively."
    };
    
    
    string bot_thoughts_user_likes[18] = 
    {"Yeah I can see how you would like them. They are very diverse and verstile. I like them, but I find them a bit plain in design that's just my opinion though.", 
    "I am personally not a fan, as they are weak to very common types. But many iconic Pokemon are fire type like Charizard so I can see the appeal.", 
    "Oh we think similarily, Water types are my favourite type as well. I love their designs and defensive-based playstyle. My favourite is Swampert.",
    "That’s fair, one of the starter Pokemon is always Grass so I can see why you would like it.",
    "Yeah, I like them as well. Something about a speedy Pokemon that also hits like a runaway freight train is an appealing concept!",
    "Okay, I can see where your coming from, Ice types have some pretty cool designs, like Mamoswine, Weavile or Walrein.",
    "For sure, they are cool, and who doesn’t like a big Attack stat, am I right?",
    "I get where your coming from, Poison types have some cool designs, but I personally find oversaturated with many weak and bland Pokemon.",
    "I see you have good taste! Ground Pokemon are just so cool are they not? Between Flygon, Garchomp, Torterra the list goes on!",
    "I can respect that. I personally dislike how saturated the type is with just regular birds though. It does have some cool Pokemon like Dragonite and Lugia though I will give you that!",
    "Yeah, some of the designs can be off putting but when you have Pokemon like Metagross or Alakazam who can really complain, am I right?",
    "I do not know if I agree with you, but the Bug type certainly does have some cool Pokemon, like Scizor and Scolipede!",
    "I personally like ground types more but to each their own! There certainly is some cool Rock types like Tyrantrum or Tyranitar. Rock type is also quite good offensively so I can see the appeal!",
    "I agree whole-heartedly! Something about the spookiness and their designs are just so mesmerizing.",
    "Yep, no disagreement there, Dragons are just cool no matter what.",
    "Yeah, they do have a lot of great looking designs! Between Bisharp and Murkrow I can not blame you for liking them!",
    "I one hundred percent agree! Steel types are just so clean looking! Almost every design for them is just wonderful!",
    "Eh, I do not blame you for liking them. In battle the typing is ridiculously good. Cannot say I myself like them though."
    };
    
    string bot_thoughts_user_dislikes[18] = 
    {"I can see where your coming from, their designs are quite plain.",
    "Yeah, I agree, they have too many common weaknesses and are a little too overused for my tastes.",
    "To each their own I suppose, I personally really love their generally defensive nature, but it is not for everybody.",
    "I can see why you would say that. They have the most weaknesses of any type and outside of a few notable exceptions are not the coolest looking design wise.",
    "Huh that is interesting, most people me included like electric types. Perhaps you do not like their generally low defenses. It is good to have your own opinion on things though!",
    "Yeah, I agree, they have cool designs like Mamoswine and Beartic but honestly the typing is resisted by and is weak to way too many things.",
    "I do not really agree with that but perhaps you find most of their designs too human-like and creepy. I’m not judging though; your opinions are your opinions.",
    "Though there are some cool ones. I generally agree with you there. The type is just oversaturated with common, non-unique Pokemon. Though I guess that is subjective.",
    "I cannot understand where your coming from on this one. Ground types have some of the coolest and unique designs in the game. Though I may be a bit biased as it is my second favourite type!",
    "For sure, there is some cool designs but for the most part the Flying typing is taking up by basic looking birds.",
    "Yeah, I can understand that response, some of them are kind of creepy looking and a bit too human like for my tastes. Though they are cool.",
    "Yep, most people do not like them because they are all very similar and mostly weak. Outside of a few exceptions, like Scizor who also Steel type, I agree.",
    "Understandable, I personally find them inferior to ground types but it has some cool Pokemon like Tyranitar.",
    "Yeah, I gotcha. Some people find them a bit creepy, especially their descriptions which often involve death or the underworld. I however adore them.",
    "Okay I am sorry, I still respect your opinion, but I think you are in the minority on that one. Dragons are cool, plain, and simple.",
    "I can respect that. Dark types tend to have really cool design but some people might find them too edgy. ",
    "Huh, cannot say I agree with you on that one. But who knows maybe you like your Pokemon more monster than metal?",
    "Yeah, I agree, there designs with a few exceptions, are a little too pink, sparkly or bright for me."
    };
    
    
    int user_liked_disliked_types[18] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}; // Type is set to two by default and changes to either 1 or 0 depending on user response.
    
    //Stat descriptions ---------------------------------------------------------------------------------------------------------------
    
    string Stat_description_array[6] = 
    {"HP or Hit Points is the amount of damage a Pokemon can take before it faints and is unusable in battle til it is healed.\nPokemon with large amounts of Hit Points like Snorlax and Blissey are treasured for their ability to soak up damage without fainting.\nSome status moves like Synthesis or Wish allow you to regain HP in battle.",
    "Attack factors in to the amount of damage a Pokemon does using Physical-based attacks such as Giga Impact, Tackle or Dragon Claw.\nPokemon with high Attack include Garchomp and Tyranitar.\nStatus moves like Swords Dance or Bulk Up raise Attack.",
    "Defense helps mitigate the amount of damage a Pokemon will take from a Physical-based attack such as Mach Punch or Take Down.\nSome Pokemon with high Defense include Steelix and Skarmory.\nSome Status moves, like Iron Defense or Cotton Guard can raise Defense.",
    "Special_Attack factors in to the amount of damage a Pokemon does using Special-based attacks such as Hyper Beam or Shadow Ball.\nSome Pokemon with high Special_Attack are Gengar, Charizard and Mewtwo.\nMoves like Calm Mind and Nasty Plot can raise Special_Attack.",
    "Special_Defense helps mitigate the amount of damage a Pokemon will take from a Physical-based attack such as Mach Punch or Take Down.\nSome Pokemon with high Special_Defense include Tentacruel and Kyogre.\nSome Status moves, like Amnesia or Cosmic Power can raise Special_Defense.",
    "Speed determines which Pokemon in the battle goes first in a turn.\nIt is very important as attacking before the opposing Pokemon could be the difference between winning and losing.\nThere is also priority moves which ignore the opposing Pokemons speed unless they are using priority moves.\nSome speedy Pokemon include Pikachu and Jolteon.\nSome Status moves like Trick Room can make the slowest Pokemon go first so watch out!"
    };
    
    // Move catagory descriptions ---------------------------------------------------------------------------------------------------------------
    string Move_catagory_desciptions[3] = 
    {"Physical moves are attacks that do damage based on the users Attack as well as various other factors such as Typing.\nSome examples of Physical attacks are Cross Chop, Thunder Fang, and Meteor Mash. They are represented by a single spiky circle symbol",
    "Special moves are attacks that do damage based on the users Special_Attack as well as various other factors such as Typing.\nSome examples of Special attacks are Hyper Beam, Flamethrower, Thunderbolt and Surf. These moves are represented by a multi-layered circle symbol",
    "Status moves are the most diverse of the three catagories. They can inflict your opponant with Status conditions.\nThese include Sleep which renders the opponant unable to preform moves, Poison which saps their HP every turn and Burn which does damage every turn and cuts the opponants Attack in half.\nThey can also be used to multiply every stat in battle outside of HP which status moves can recover.\nI could go on but then we would be on this topic for hours!"
    };
    
    // End of Private variables ---------------------------------------------------------------------------------------------------------------
    
    public:
    
    Chatbot(string name)
    {
        chatbot_name = name;
    }
    
    //The Yes or No decision Function---------------------------------------------------------------------------------------------------------------
    
    int yes_no(vector<string> broken_words, string input)
    {
        int yes_amount = 0;
        int no_amount = 0;
        
        for(int word_index = 0; word_index < broken_words.size(); word_index++) //Analyses text pattern, If the chatbot finds a contradictory word in the input or broken_words it will return the value to ask again.
        {
            if(find(Potential_contradiction.begin(), Potential_contradiction.end(), input) != Potential_contradiction.end() || find(Potential_contradiction.begin(), Potential_contradiction.end(), broken_words[word_index]) != Potential_contradiction.end())
            {
                return 2;
            }
        }
        
        for(int word_index = 0; word_index < broken_words.size(); word_index++)
        {
            if(find(Potential_yes.begin(), Potential_yes.end(), input) != Potential_yes.end() || find(Potential_yes.begin(), Potential_yes.end(), broken_words[word_index]) != Potential_yes.end())
            {
                yes_amount += 1;
                
            }
            
            else if(find(Potential_no.begin(), Potential_no.end(), input) != Potential_no.end() || find(Potential_no.begin(), Potential_no.end(), broken_words[word_index]) != Potential_no.end())
            {
                no_amount += 1;
            }
            
            
        }
        
        if(yes_amount > 0 && no_amount == 0)
        {
            yes_or_no_flag = 0;
            return 1;
        }
        
        else if(no_amount > 0 && yes_amount == 0)
        {
            yes_or_no_flag = 0;
            return 0;
        }
        
        // In any other scenario, the bot will ask for clarification on the answer.
        return 2;
        
        
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    
    
    //Function that returns a users thoughts on each type. ---------------------------------------------------------------------------------------------------------------
    string user_type_thoughts()
    {
        string full_type_thought_response;
        
        for(int type_thought_counter = 0; type_thought_counter < 18; type_thought_counter++)
        {
            if(user_liked_disliked_types[type_thought_counter] == 1)
            {
                full_type_thought_response += "You have told me that you like " + Upper_case_type_database[type_thought_counter] + " types. ";
            }
            else if(user_liked_disliked_types[type_thought_counter] == 0)
            {
                full_type_thought_response += "You have told me that you dislike " + Upper_case_type_database[type_thought_counter] + " types. ";
            }
            else
            {
                full_type_thought_response += "You have not told me what you think about " + Upper_case_type_database[type_thought_counter] + " types. ";
            }
            
            if(type_thought_counter == 3 || type_thought_counter == 6 || type_thought_counter == 9 || type_thought_counter == 12 || type_thought_counter == 15) // Every third sentance do a newline.
            {
                full_type_thought_response += "\n";
            }
        }
        
        return full_type_thought_response;
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    
    
    
    // Tell Function------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    void tell(string input) // Receives and processes the input
    {
        true_keyword = "";
        
        istringstream iss(input); //Concept and idea learned from here: https://stackoverflow.com/questions/236129/how-do-i-iterate-over-the-words-of-a-string
        for(string input; iss >> input;) //Breaks input into words and stores them in the vector<string>: broken_words.
        {
            broken_words.push_back(input);
        }
        
        
        // Yes or No Question input ---------------------------------------------------------------------------------------------------------------
        
        if(yes_or_no_flag == 1) // If a yes or no question has been triggered previously
        {
            yes_no_response = yes_no(broken_words, input);
            true_keyword = previous_keyword;
        }
        
        // Reserved for initial greetings
        // First Greeting-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        else if(greeting == 1)
        {
        int found_in_greetings = 0;
            
            for(int greetings_finder = 0; greetings_finder < broken_words.size(); greetings_finder++)
            {
                if(find(Potential_greetings.begin(), Potential_greetings.end(), broken_words[greetings_finder]) != Potential_greetings.end())
                {
                    found_in_greetings = 1;
                }
            }
            
            if(find(Potential_greetings.begin(), Potential_greetings.end(), input) != Potential_greetings.end() || found_in_greetings == 1) // Evaluates whole input as well as word-by-word
            {
                true_keyword = "First greeting";
            }   
            
            else
            {
                true_keyword = "Misunderstood First greeting";
                    
            }
        }
        
        //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // This part goes when the conversation is past initial greetings and it is not a yes_no question.
        
        else
        {
        
            // If the chatbot remembers this input. -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            
            if(find(unknown_memory.begin(), unknown_memory.end(), input) != unknown_memory.end()) 
            {
                auto found_keyword = find(unknown_memory.begin(), unknown_memory.end(), input);
                keyword_index = distance(unknown_memory.begin(), found_keyword);
                remembering_flag = 1;
            
            }
            
            //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            
            for(int j = 0; j < broken_words.size(); j++) // Evaluates the broken down input word by word with the various databases. Only place in program a variable name is unrelated j because it is used in so many places a larger variable would look messy and hinder readability. 
            {
            
                // Next Iterate the keywords within input through type_database -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                
                if(find(Type_intro_database.begin(), Type_intro_database.end(), broken_words[j]) != Type_intro_database.end()) // If a matching keyword is found within the lower_case_type_database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Type_intro_database.begin(), Type_intro_database.end(), broken_words[j]);
                    keyword_index = distance(Type_intro_database.begin(), found_keyword);
                }
                
                if(find(lower_case_type_database.begin(), lower_case_type_database.end(), broken_words[j]) != lower_case_type_database.end()) // If a matching keyword is found within the lower_case_type_database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(lower_case_type_database.begin(), lower_case_type_database.end(), broken_words[j]);
                    keyword_index = distance(lower_case_type_database.begin(), found_keyword);
                }
            
                if(find(Upper_case_type_database.begin(), Upper_case_type_database.end(), broken_words[j]) != Upper_case_type_database.end()) // If a matching keyword is found within the Upper_case_type_database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Upper_case_type_database.begin(), Upper_case_type_database.end(), broken_words[j]);
                    keyword_index = distance(Upper_case_type_database.begin(), found_keyword);
                }
                
                // IVs and EVs -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                if(find(IVs.begin(), IVs.end(), broken_words[j]) != IVs.end()) // If a matching keyword is found within the IVs database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(IVs.begin(), IVs.end(), broken_words[j]);
                    keyword_index = distance(IVs.begin(), found_keyword);
                }
                
                if(find(EVs.begin(), EVs.end(), broken_words[j]) != EVs.end()) // If a matching keyword is found within the EVs database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(EVs.begin(), EVs.end(), broken_words[j]);
                    keyword_index = distance(EVs.begin(), found_keyword);
                }
                // Stats -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                
                if(find(Stats.begin(), Stats.end(), broken_words[j]) != Stats.end()) // If a matching keyword is found within the Stats database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Stats.begin(), Stats.end(), broken_words[j]);
                    keyword_index = distance(Stats.begin(), found_keyword);
                }
                
                if(find(lower_case_stats_database.begin(), lower_case_stats_database.end(), broken_words[j]) != lower_case_stats_database.end()) // If a matching keyword is found within the Move_catagory database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(lower_case_stats_database.begin(), lower_case_stats_database.end(), broken_words[j]);
                    keyword_index = distance(lower_case_stats_database.begin(), found_keyword);
                }
                
                if(find(Upper_case_stats_database.begin(), Upper_case_stats_database.end(), broken_words[j]) != Upper_case_stats_database.end()) // If a matching keyword is found within the Move_catagory database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Upper_case_stats_database.begin(), Upper_case_stats_database.end(), broken_words[j]);
                    keyword_index = distance(Upper_case_stats_database.begin(), found_keyword);
                }
            
                if(find(Partial_case_stats_database.begin(), Partial_case_stats_database.end(), broken_words[j]) != Partial_case_stats_database.end()) // If a matching keyword is found within the Move_catagory database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Partial_case_stats_database.begin(), Partial_case_stats_database.end(), broken_words[j]);
                    keyword_index = distance(Partial_case_stats_database.begin(), found_keyword);
                }
                
                //Users Liked and Disliked Types -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                
                if(find(User_thoughts.begin(), User_thoughts.end(), broken_words[j]) != User_thoughts.end()) // If a matching keyword is found within the User_thoughts database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(User_thoughts.begin(), User_thoughts.end(), broken_words[j]);
                    keyword_index = distance(User_thoughts.begin(), found_keyword);
                }
                
                // Moves -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                
                if(find(Moves.begin(), Moves.end(), broken_words[j]) != Moves.end()) // If a matching keyword is found within the Moves database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Moves.begin(), Moves.end(), broken_words[j]);
                    keyword_index = distance(Moves.begin(), found_keyword);
                }
                
                if(find(Move_catagories_lower_case.begin(), Move_catagories_lower_case.end(), broken_words[j]) != Move_catagories_lower_case.end()) // If a matching keyword is found within the Move_catagory database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Move_catagories_lower_case.begin(), Move_catagories_lower_case.end(), broken_words[j]);
                    keyword_index = distance(Move_catagories_lower_case.begin(), found_keyword);
                }
                
                if(find(Move_catagories_Upper_case.begin(), Move_catagories_Upper_case.end(), broken_words[j]) != Move_catagories_Upper_case.end()) // If a matching keyword is found within the Move_catagory database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Move_catagories_Upper_case.begin(), Move_catagories_Upper_case.end(), broken_words[j]);
                    keyword_index = distance(Move_catagories_Upper_case.begin(), found_keyword);
                }
                
                // Evolution -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
                if(find(Evolution_database.begin(), Evolution_database.end(), broken_words[j]) != Evolution_database.end()) // If a matching keyword is found within the Move_catagory database vector
                {
                    current_topic.push_back(broken_words[j]);
                    auto found_keyword = find(Evolution_database.begin(), Evolution_database.end(), broken_words[j]);
                    keyword_index = distance(Evolution_database.begin(), found_keyword);
                }
                
                //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            
            }
            
            // Unknown, Learning, Remembered Process -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            if(learning_flag == 1) //If the user previously entered an unknown input (an input that did not match anything in any of the databases being compared)
            {
                true_keyword = "Learning";
                learned_memory.push_back(input);
                current_topic.erase(current_topic.begin(), current_topic.end());
                broken_words.erase(broken_words.begin(), broken_words.end());
            }
        
            if(remembering_flag == 1)
            {
                true_keyword = "Remembered";
                current_topic.erase(current_topic.begin(), current_topic.end());
                broken_words.erase(broken_words.begin(), broken_words.end());
            }
            //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
            // Regular flow of input
            
            if(1 < current_topic.size())
            {
                true_keyword = "More than One";
                broken_words.erase(broken_words.begin(), broken_words.end());
            }
        
        
            else if(current_topic.size() == 1)
            {
                true_keyword = current_topic[0];
                current_topic.erase(current_topic.begin(), current_topic.end());
                broken_words.erase(broken_words.begin(), broken_words.end());
            }
        
            else if(broken_words.size() != 0 && learning_flag != 1 && remembering_flag != 1 && input != "") //If the users input contained words or spaces but was not blank.
            {
                true_keyword = "unknown";
                unknown_memory.push_back(input);
                current_topic.erase(current_topic.begin(), current_topic.end());
                broken_words.erase(broken_words.begin(), broken_words.end());
            }
        
        }
    }
    
    // Response Function------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    
    string get_reply() // Gets an appropriate response based on input
    {
        // Two most important high priority responses - Empty response and the Neither yes or no response.
        
        
        if(yes_or_no_flag == 1)
        {
            broken_words.erase(broken_words.begin(), broken_words.end());
            return not_yes_or_no[rand() % 2];
        }
        
        if(true_keyword == "")
        {
            return empty_responses[rand() % 4];
        }
        
        // Initial Greeting only goes once.---------------------------------------------------------------------------------------------------------------
        if(greeting == 1)
        {
            if(yes_no_response == 1)
            {
                previous_keyword = "";
                yes_no_response = 2;
                greeting = 0;
                string already_know = "So you already know. That's great! Well";
                return already_know+job_response;
                
            }
            else if(yes_no_response == 0)
            {
                previous_keyword = "";
                yes_no_response = 2;
                greeting = 0;
                return Beginner_intro+job_response;
                
            }
            else
            {
                previous_keyword = "Greeting";
                if(true_keyword == "First greeting")
                { 
                    if(find(broken_words.begin(), broken_words.end(), "how") != broken_words.end() || find(broken_words.begin(), broken_words.end(), "how's") != broken_words.end() || find(broken_words.begin(), broken_words.end(), "How") != broken_words.end() || find(broken_words.begin(), broken_words.end(), "How's") != broken_words.end())
                    {
                        yes_or_no_flag = 1;
                        broken_words.erase(broken_words.begin(), broken_words.end());
                        return initial_greeting_how_responses[rand() % 3]+job_initiation[rand() % 5]; //If the initial greeting is recognize and has a "how" in any text pattern the person is likely asking how the chatbot is feeling. So it will add to its response how its feeling
                    }
                    
                    yes_or_no_flag = 1;
                    broken_words.erase(broken_words.begin(), broken_words.end());
                    return initial_greeting_responses[rand() % 3]+job_initiation[rand() % 5]; // If the user does not ask anything regarding the chatbot's initial feelings. It will respond without mentioning it's emotions.
                }
                if(greeting == 1 && true_keyword == "Misunderstood First greeting")
                {
                    yes_or_no_flag = 1;
                    broken_words.erase(broken_words.begin(), broken_words.end());
                    return misunderstood_greetings[rand() % 3]+job_initiation[rand() % 5];
                }
        
            }
        }
        
        //--------------------------------------------------------------------------------------------------------------
        
        if(true_keyword == "unknown") // Used by the response function if the users input does not contain any keyword in the chatbot's database
        {
           learning_flag = 1;
           return unknown_chat[rand() % 3];
        }
        
        
        else if(true_keyword == "Learning" && learning_flag == 1)
        {
            learning_flag = 0;
            string full_learned_response = learning_responses[rand() % 5] + learned_response_add_on; 
            return full_learned_response;
        }
        
        else if(true_keyword == "Remembered")
        {
            remembering_flag = 0;
            string full_remembered_response = remembered_responses[rand() % 1] + learned_memory[keyword_index];
            return full_remembered_response;
        }
        
        else if(true_keyword == "More than One")
        {
            string Excess_keyword_response = multiple_keywords[rand() % 2];
            for(int current_topic_adder = 0; current_topic_adder < current_topic.size(); current_topic_adder++)
            {
                Excess_keyword_response += current_topic[current_topic_adder];
                if(current_topic_adder != current_topic.size() - 1)
                {
                Excess_keyword_response += ", ";
                }
                else
                {
                Excess_keyword_response += " ";   
                }
            }
            current_topic.erase(current_topic.begin(), current_topic.end());
            return Excess_keyword_response;
        }
        
        // Beginning of Pokemon based responses.
        // -----------------------------------------------------------------------
        // Instead of searching for the keyword in the database again, uses the previously established variable: keyword_index, to locate it immediatly don't need to worry about keyword_index being overwritten as that is
        // By the response above this. If the response makes it here there should be only one keyword
        
        else if(true_keyword == lower_case_type_database[keyword_index] || true_keyword == Upper_case_type_database[keyword_index])
        {
            if(yes_no_response == 1)
            {
                previous_keyword = "";
                yes_no_response = 2;
                user_liked_disliked_types[keyword_index] = 1;
                cout << keyword_index;
                return bot_thoughts_user_likes[keyword_index]+I_will_remember_that+anything_else;
                
            }
            else if(yes_no_response == 0)
            {
                previous_keyword = "";
                yes_no_response = 2;
                user_liked_disliked_types[keyword_index] = 0;
                cout << keyword_index;
                return bot_thoughts_user_dislikes[keyword_index]+I_will_remember_that+anything_else;
            }
            else
            {
            previous_keyword = true_keyword;
            string like_type_question = " Do you like " + Upper_case_type_database[keyword_index] + " types?";
            string type_explanation_and_question = type_responses_super_array[keyword_index] + like_type_question;
            yes_or_no_flag = 1;
            return type_explanation_and_question;
            }
        }
        
        else if(true_keyword == Type_intro_database[keyword_index])
        {
            return type_intro+anything_else;
        }
        // EVs and IVs -----------------------------------------------------------------------
        else if(true_keyword == EVs[keyword_index])
        {
            return EVs_intro+anything_else;
        }
        
        else if(true_keyword == IVs[keyword_index])
        {
            return IVs_intro+anything_else;
        }
        // Stats -----------------------------------------------------------------------
        
        else if(true_keyword == Stats[keyword_index])
        {
            return stats_intro+anything_else;
        }
        
        else if(true_keyword == lower_case_stats_database[keyword_index] || true_keyword == Upper_case_stats_database[keyword_index] || true_keyword == Partial_case_stats_database[keyword_index])
        {
            return Stat_description_array[keyword_index]+anything_else;
        }
        // Users liked and disliked types -----------------------------------------------------------------------
        
        else if(true_keyword == User_thoughts[keyword_index])
        {
            string Loaded_User_Response = user_type_thoughts();
            return Loaded_User_Response + anything_else;
        }
        // Moves -----------------------------------------------------------------------
        
        else if(true_keyword == Moves[keyword_index])
        {
            return Moves_intro + anything_else;
        }
        
        else if(true_keyword == Move_catagories_lower_case[keyword_index] || true_keyword == Move_catagories_Upper_case[keyword_index])
        {
            return Move_catagory_desciptions[keyword_index]+anything_else;
        }
        // Evolution -----------------------------------------------------------------------
        else if(true_keyword == Evolution_database[keyword_index])
        {
            return evolution_intro+anything_else;
        }
        
        
        
        
    string last_resort = "Wow I have no idea how to respond to that. I'm genuinely shocked right now. Could you maybe try asking me something about Pokemon?";
    return last_resort;
        
    }
    
    
    string get_name() // Tells the user its name
    {
        return chatbot_name;
    }
    
};