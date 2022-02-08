Παναγιώτης Μαυρομμάτης - 1115201800115 - sdi1800115
1η εργασία SysPro 2021

Για την εκτέλεση:
Κάνουμε extract το αρχείο και τρέχουμε τις εξής εντολές:
make //Για να γίνει compile το πρόγραμμα, το εκτελέσιμο βγαίνει στον φάκελο build
cd build
chmod 777 testFile.sh //Για να μπορέσουμε να τρέξουμε με ./ το Bash Script
./testFile.sh virusesFile countriesFile 1000 1 //Για να δημιουργηθεί το inputfile
Ώπου 1000 numlines και 1 για duplicates όπως αναφέρεται και στην εκφώνηση
./vaccineMonitor -c inputfile -b 100000 //Για να τρέξουμε το πρόγραμμα

Αρχεία ανα φάκελο:
Στο φάκελο build περιέχεται το bash script (testFile.sh) και τα 2 αρχεία που περιέχουν χώρες και ιούς
αντίστοιχα. Τρέχοντας το bashscript δημιουργείται και το inputfile.
Επιπλέον το εκτελέσιμο του βασικού προγράμματος βγαίνει σε αυτόν τον φάκελο.
Στον φάκελο examples περιέχεται το αρχείο main.c, που περιέχει την main συνάρτηση για το vaccineMonitor.
Στον φάκελο src περιέχονται 6 .c αρχεία που περιέχουν συναρτήσεις που χρειάζεται το πρόγραμμα. Πιο συγκεκριμένα στο αρχείο
bloomfilter.c περιέχεται ο κώδικας που μας δόθηκε στο piazza για το bloom filter. Στο αρχείο bloomFunctions.c περιέχονται οι
συναρτήσεις που χρησιμοποιούνται για την δημιουργία του bloom filter. Αντίστοιχα στο skipListFunctions.c περιέχονται οι συναρτήσεις
που χρειάζονται για την δημιουργία των skip lists. Στο αρχείο mainQuestionsFunctions.c βρίσκονται οι συναρτήσεις που μας ζητείτε να 
υλοποιησουμε απο την εκφώνηση. Στο BST.c βρίσκονται βοηθητικές συναρτήσεις για τα binary search trees που έχω υλοποιήσει για τους ιούς
και τις χώρες. Τέλος στο αρχείο StartersAndHelpFunctions.c περιέχονται οι πιο βασικές συναρτήσεις του προγράμματος, όπως το αρχικό διάβασμα
από τα αρχεία, το διάβασμα των εντολών που δίνει ο χρήστης, την δημιουργία των προαναφερόμενων δυαδικών δένδρων και την δημιουργία
της βασικής single linked list.
Στον φάκελο include περιέχονται τα αντίστοιχα headerFiles των .c αρχείων που αναφέρω παραπάνω. Επίσης περιέχεται και το structs.h, το οποίο περιέχει
defines για το μέγιστο και ελάχιστο βάθος της SkipList, για το μέγιστο μήκος γραμμής, για το πλήθος των hash functions για το bloom filterκαθώς και 
τις δηλώσεις των structs που χρησιμοποιούνται στο πρόγραμμα.

Ζητάω συγγνώμη αν σε κάποια σημεία μου έχουν ξεφύγει comments στα αγγλικά, απλώς είχα ξεκινήσει να γράφω στα αγγλικά αλλά στην πορεία το μετάνιωσα.....

Στο ReadMe εξηγώ κυρίως την λογική και τον τρόπο λειτουργίας των προγραμμάτων μου, ενώ στα σχόλια εξηγώ ακριβώς τι κάνω.
Για οποιαδήποτε τυχών απορία στο πρόγραμμα μου, παρακαλώ να ανατρέξετε στα σχόλια που υπάρχουν για κάθε συνάρτηση.

Σχετικά με το Bash Script:
Ξεκινώντας από την "main", δηλαδή από την γραμμή 88, γίνεται διαγραφή αν υπάρχει ήδη αρχείο με όνομα inputfile. Έπειτα, γίνεται έλεγχος για το πλήθος των ορισμάτων
και σε περίπτωση λάθους εμφανίζεται αντίστοιχο μήνυμα και τερματίζει το πρόγραμμα. Στην συνέχεια αποθηκεύουμε σε μεταβλητές τα ορίσματα. Αν υπάρχει το αρχείο με τους 
ιούς τότε το διαβάζουμε και το αποθηκεύουμε. Διαφορετικά εμφανίζεται αντίστοιχο μήνυμα Η ίδια διαδικασία ακολουθείτε και για το αρχείο με τις χώρες. Στην συνέχεια, για
όσες γραμμές μας ζητείται να δημιουργήσουμε γίνεται η εξής διαδικασία: Με την RANDOM παίρνουμε έναν αριθμό από 0-9999 και με την βοήθεια της συνάρτησης duplicate_id φροντίζουμε 
να μην έχει ξαναχρησιμοποιηθεί αυτός ο αριθμός και το εκτυπώνουμε στο inputfile. Έπειτα, χρησιμοποιώντας την συνάρτηση get_name, δημιουργούμε από ένα random αλφαριθμητικό για firstname και
lastname και τα εκτυπώνουμε στο inputfile. Επιλέγουμε με την random χώρα από τον πίνακα και ηλικία και τα εκτυπώνουμε στο inputfile. Για την επιλογή του ιού χρησιμοποιούμε την συνάρτηση Country_virus_yesno_date, μέσω της οποίας επιλέγεται στην τύχη ιός, και YES η NO. Σε περίπτωση που είναι YES, χρησιμοποιώντας και πάλι την random φτιάχνουμε και ημερομηνία. Αν βρισκόμαστε στην τελευταία γραμμή που πρέπει να υπολογίσουμε, 
εκτυπώνουμε τα παραπάνω στο inputfile χωρίς αλλαγή γραμμής, διαφορετικά με αλλαγή γραμμής. 
Το ίδιο και στην περίπτωση που δεν έχει κάνει εμβόλιο. Τέλος, άμα επιτρέπονται τα duplicates υπάρχει μια πιθανότητα 10% για την ύπαρξη τους.

Σχετικά με το vaccineMonitor:
Ξεκινώντας από την main, γίνεται έλεγχος για το πλήθος των ορισμάτων. Στην συνέχεια με την βοήθεια της processFile και των υπόλοιπων συναρτήσεων που καλούνται από αυτήν, δημιουργείται 1 single linked list, όπου κάθε κόμβος της
αναφέρεται σε ένα εμβόλιο για έναν ιό για κάποιον citizen, και από ένα binary search tree για τους ιούς και τις χώρες αντίστοιχα. Αυτό γίνεται για να μην υπάρχει μεγάλη επανάληψη πληροφορίας και χάνετε χώρος στην μνήμη, αφού, 
με αυτόν τον τρόπο κάθε citizen, δηλαδή κόμβος της λίστας, που έχει ίδια χώρα καταγωγής ή αναφέρεται στον ίδιο ιο θα δείχνει στην ίδια διεύθυνση, η οποία είναι αυτή στην οποία βρίσκεται ο αντίστοιχος κόμβος του δέντρου. Στην συνέχεια, χρησιμοποιώντας την linked list που κατασκευάστηκε, δημιουργείται και το bloom filter.
Κάθε ιός αντιστοιχεί σε μία γραμμή του πίνακα bArrays, η οποία είχε ήδη αποθηκευτεί κατά την δημιουργία του bst για τα virus. Στην συνέχεια δημιουργούνται και οι 
skipLists. O πίνακας Table_of_Heads, ο οποίος έχει μέγεθος 2 * πλήθος ιών, περιέχει από 2 Skip Lists για κάθε ιό. Μία για όσους έχουν εμβολιαστεί και μια για όσους όχι. Όπως αναφέρεται και στα σχόλια, 
ουσιαστικά κάθε Skip List αποτελείται από 1 single linked list για ΚΑΘΕ βάθος/ύψος. Στην συνεχεία έχουμε την κύρια "λούπα" του προγράμματος όπου ο χρήστης δίνει εντολές. Τέλος, όταν η εντολή που δώσει ο χρήστης είναι /exit, 
το πρόγραμμα ελευθερώνει τον δυναμικά δεσμευμένο χώρο στην μνήμη και κλείνει.

Θεωρώ ότι το πρόγραμμά μου είναι πλήρες, με εξαίρεση ίσως κάποια ελάχιστα memory leaks (<100 bytes) που προκύπτουν από τις strdup στην συνάρτηση insert_new_citizen_record, άρα και κατά επέκταση στην vaccinate_Now. 
Θα ήθελα να σημειώσω πως στις 2 προαναφερόμενες συναρτήσεις, θεωρώ πως ο τρόπος που ενημερώνω τις SkipLists μου, είτε χρειάζεται ένα απλό update δηλαδή μεταφορά από την NO SkipList στην YES ή 
απλή εισαγωγή νέου κόμβου σε ήδη υπάρχων Skip List, είτε χρείαζεται η δημιουργεία κάποιων εξ ολοκλήρου καινούριων skipList είναι ο πιο αποδοτικός και λιγότερο χρονοβόρο. Αντίθετα, το bloom filter σε κάθε περίπτωση,
 το διαγράφω και το αναδημιουργώ με τα νέα στοιχειά. Σε περίπτωση που υπήρχανε πάρα πολλά δεδομένα αυτό θα μπορούσε να είναι αρκετά χρονοβόρο, αλλά από τις δοκιμές που έκανα δεν παρατήρησα κάτι τέτοιο. 
Ωστόσο, και σε αυτήν την περίπτωση δεν χρησιμοποιείται περισσότερη μνήμη από ότι χρειάζεται. 

Greeklish σε περίπτωση που δεν μπορείται να το διαβάσετε:
Greeklish se periptwsi pou den mporeitai na to diavasete:

Panagiwtis Mavrommatis - 1115201800115 - sdi1800115
1i ergasia SysPro 2021

Gia tin ektelesi:
Kanoume extract to arxeio kai trexoume tis eksis entoles:
make //Gia na ginei compile to programma, to ektelesimo vgainei ston fakelo build
cd build
chmod 777 testFile.sh //Gia na mporesoume na treksoume me ./ to Bash Script
./testFile.sh virusesFile countriesFile 1000 1 //Gia na dimiourgithei to inputfile
Wpou 1000 numlines kai 1 gia duplicates opws anaferetai kai stin ekfwnisi
./vaccineMonitor -c inputfile -b 100000 //Gia na treksoume to programma

Arxeia ana fakelo:
Sto fakelo build periexetai to bash script (testFile.sh) kai ta 2 arxeia pou periexoun xwres kai ioys
antistoixa. Trexontas to bashscript dimiourgeitai kai to inputfile.
Epipleon to ektelesimo tou vasikoy programmatos vgainei se afton ton fakelo.
Ston fakelo examples periexetai to arxeio main.c, pou periexei tin main synartisi gia to vaccineMonitor.
Ston fakelo src periexontai 6 .c arxeia pou periexoun synartiseis pou xreiazetai to programma. Pio sygkekrimena sto arxeio
bloomfilter.c periexetai o kwdikas pou mas dothike sto piazza gia to bloom filter. Sto arxeio bloomFunctions.c periexontai oi
synartiseis pou xrisimopoioyntai gia tin dimiourgia tou bloom filter. Antistoixa sto skipListFunctions.c periexontai oi synartiseis
pou xreiazontai gia tin dimiourgia twn skip lists. Sto arxeio mainQuestionsFunctions.c vriskontai oi synartiseis pou mas ziteite na 
ylopoiisoume apo tin ekfwnisi. Sto BST.c vriskontai voithitikes synartiseis gia ta binary search trees pou exw ylopoiisei gia tous ioys
kai tis xwres. Telos sto arxeio StartersAndHelpFunctions.c periexontai oi pio vasikes synartiseis tou programmatos, opws to arxiko diavasma
apo ta arxeia, to diavasma twn entolwn pou dinei o xristis, tin dimiourgia twn proanaferomenwn dyadikwn dendrwn kai tin dimiourgia
tis vasikis single linked list.
Ston fakelo include periexontai ta antistoixa headerFiles twn .c arxeiwn pou anaferw parapanw. Episis periexetai kai to structs.h, to opoio periexei
defines gia to megisto kai elaxisto vathos tis SkipList, gia to megisto mikos grammis, gia to plithos twn hash functions gia to bloom filterkathws kai 
tis dilwseis twn structs pou xrisimopoioyntai sto programma.

Zitaw syggnwmi an se kapoia simeia mou exoun ksefygei comments sta agglika, aplws eixa ksekinisei na grafw sta agglika alla stin poreia to metaniwsa.....

Sto ReadMe eksigw kyriws tin logiki kai ton tropo leitourgias twn programmatwn mou, enw sta sxolia eksigw akrivws ti kanw.
Gia opoiadipote tyxwn aporia sto programma mou, parakalw na anatreksete sta sxolia pou yparxoun gia kathe synartisi.

Sxetika me to Bash Script:
KSekinwntas apo tin "main", diladi apo tin grammi 88, ginetai diagrafi an yparxei idi arxeio me onoma inputfile. Epeita, ginetai elegxos gia to plithos twn orismatwn
kai se periptwsi lathous emfanizetai antistoixo minyma kai termatizei to programma. Stin synexeia apothikeyoume se metavlites ta orismata. An yparxei to arxeio me tous 
ioys tote to diavazoume kai to apothikeyoume. Diaforetika emfanizetai antistoixo minyma I idia diadikasia akoloutheite kai gia to arxeio me tis xwres. Stin synexeia, gia
oses grammes mas ziteitai na dimiourgisoume ginetai i eksis diadikasia: Me tin RANDOM pairnoume enan arithmo apo 0-9999 kai me tin voitheia tis synartisis duplicate_id frontizoume 
na min exei ksanaxrisimopoiithei aftos o arithmos kai to ektypwnoume sto inputfile. Epeita, xrisimopoiwntas tin synartisi get_name, dimiourgoyme apo ena random alfarithmitiko gia firstname kai
lastname kai ta ektypwnoume sto inputfile. Epilegoume me tin random xwra apo ton pinaka kai ilikia kai ta ektypwnoume sto inputfile. Gia tin epilogi tou ioy xrisimopoioyme tin synartisi Country_virus_yesno_date, mesw tis opoias epilegetai stin tyxi ios, kai YES i NO. Se periptwsi pou einai YES, xrisimopoiwntas kai pali tin random ftiaxnoume kai imerominia. An vriskomaste stin teleftaia grammi pou prepei na ypologisoume, 
ektypwnoume ta parapanw sto inputfile xwris allagi grammis, diaforetika me allagi grammis. 
To idio kai stin periptwsi pou den exei kanei emvolio. Telos, ama epitrepontai ta duplicates yparxei mia pithanotita 10% gia tin yparksi tous.

Sxetika me to vaccineMonitor:
KSekinwntas apo tin main, ginetai elegxos gia to plithos twn orismatwn. Stin synexeia me tin voitheia tis processFile kai twn ypoloipwn synartisewn pou kaloyntai apo aftin, dimiourgeitai 1 single linked list, opou kathe komvos tis
anaferetai se ena emvolio gia enan io gia kapoion citizen, kai apo ena binary search tree gia tous ioys kai tis xwres antistoixa. Afto ginetai gia na min yparxei megali epanalipsi pliroforias kai xanete xwros stin mnimi, afoy, 
me afton ton tropo kathe citizen, diladi komvos tis listas, pou exei idia xwra katagwgis i anaferetai ston idio io tha deixnei stin idia dieythynsi, i opoia einai afti stin opoia vrisketai o antistoixos komvos tou dentrou. Stin synexeia, xrisimopoiwntas tin linked list pou kataskevastike, dimiourgeitai kai to bloom filter.
Kathe ios antistoixei se mia grammi tou pinaka bArrays, i opoia eixe idi apothikeftei kata tin dimiourgia tou bst gia ta virus. Stin synexeia dimiourgoyntai kai oi 
skipLists. O pinakas Table_of_Heads, o opoios exei megethos 2 * plithos iwn, periexei apo 2 Skip Lists gia kathe io. Mia gia osous exoun emvoliastei kai mia gia osous oxi. Opws anaferetai kai sta sxolia, 
ousiastika kathe Skip List apoteleitai apo 1 single linked list gia KATHE vathos/ypsos. Stin synexeia exoume tin kyria "loypa" tou programmatos opou o xristis dinei entoles. Telos, otan i entoli pou dwsei o xristis einai /exit, 
to programma eleftherwnei ton dynamika desmevmeno xwro stin mnimi kai kleinei.

THewrw oti to programma mou einai plires, me eksairesi isws kapoia elaxista memory leaks (<100 bytes) pou prokyptoun apo tis strdup stin synartisi insert_new_citizen_record, ara kai kata epektasi stin vaccinate_Now. 
THa ithela na simeiwsw pws stis 2 proanaferomenes synartiseis, thewrw pws o tropos pou enimerwnw tis SkipLists mou, eite xreiazetai ena aplo update diladi metafora apo tin NO SkipList stin YES i 
apli eisagwgi neou komvou se idi yparxwn Skip List, eite xreiazetai i dimiourgeia kapoiwn eks oloklirou kainoyriwn skipList einai o pio apodotikos kai ligotero xronovoro. Antitheta, to bloom filter se kathe periptwsi,
 to diagrafw kai to anadimiourgw me ta nea stoixeia. Se periptwsi pou ypirxane para polla dedomena afto tha mporoyse na einai arketa xronovoro, alla apo tis dokimes pou ekana den paratirisa kati tetoio. 
Wstoso, kai se aftin tin periptwsi den xrisimopoieitai perissoteri mnimi apo oti xreiazetai.
