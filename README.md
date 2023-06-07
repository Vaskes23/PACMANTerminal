<h1>Presne specifikace semestralni prace</h1>

<h2>Zadani z progtestu</h2>
Strucne pripomenu zadani semestralni prace, me vybrane zadani semestralni prace je udelat hru PacMan, hra se musi
ramcove
drzet pravidlum puvodni hry, vyuzit polymofismus, ruzne chovoani duchu, implementace zakladnich hernich mechanik,
vizualni
reprezenrace prvku ve hre, zobrazovat tabulku hracu a konfigurovani ze souboru.

<h2>Me rozsireni zadani</h2>
Take jsem se rozhodl pro rozsireni zadani v techto aspektech hry:
<ul>1. Pri zapnuti hry je na zacatky za pomoci ncurses UI interface ve forme interaktivniho menu pro nastaveni jmena, obtiznosti, chovani duchu, 
    vysvetleni hernich mechanik, spusteni hry atd. V tomto menu se muze hrac orientovat pomoci sipek a s prpinanim se meni barvy tlacitek
a po stisknuti enter potvrdi sve volby<br>
    2. Moznost hrani dvou hracu najednou ve stejne mape (multiplayer) kde by slo ve hre o to ktery ze dvou hracu vydrzi 
    dele nazivu a nebude zabit duchy a nebo nasbira vice bodu. Tuto moznost hry si bude hrac moci navolit v hernim menu pri zacatku hry<br>
    3. Zasazeni do nejakeho zakladniho pribehu a moznost prechazet mezi ruznymi mapami s pouzitim teleportu. Kde pacman projde jednim teleportem do jine nactene mapy a bude tam muset napriklad posbirat nejake spcificke predmety pro ziskani dalsich bonusu. <br>
    4. Pridani dalsiho bonusoveho ovoce pro dalsi schopnosti, napr. jablka zvysi pacmanovi rychlost, banany mu pridaji zivot
    a tresne umozni jist duchy jako v originale. Tyto ovoce bude hrac moci nastavit ve soubory ve kterem si bude take moci vytvorit svou vlastni mapu<br>
</ul>

<h2>Popis herni struktury</h2>

<ol>Třída CGame (třída, která spojuje všechny ostatní herní třídy dohromady)
      <li>CTake (pro různé akce, když Pacman narazí na objekty)
        <ol>
          <li>CPort (pro teleporty na mapě)</li>
          <li>CPoint (pro přijímání bodů, které Pacman sbírá, a jejich počítání)</li>
          <li>CFruit (pro používání schopností jako je pojídání duchů nebo zvýšení rychlosti a podobně)
            <ol>
              <li>CCherry (pro pojídání duchů)</li>
              <li>CApple (pro zvýšení rychlosti)</li>
              <li>CBanana (pro získání dalšího života)</li>
            </ol>
          </li>
        </ol>
      </li>
      <li>CPrint (pro tisknutí objektů ve hře, jako jsou mapy, menu atd.)
        <ol>
          <li>CUIMenu (pro otevření uživatelského rozhraní, kde hráč vybírá mapu, obtížnost, jméno atd.)</li>
          <li>CData (pro sběr a práci s dlouhodobými daty hry)
            <ol>
              <li>CScore (pro počítání skóre nejlepších hráčů a jeho zobrazování)</li>
              <li>CMake (pro vytváření mapy a vytváření všech dalších věcí potřebných pro Pacmana)
                <ol>
                  <li>CMapstructure (pro vytváření map z přečtených map)</li>
                </ol>
              </li>
            </ol>
          </li>
        </ol>
      </li>
      <li>CMove (pro vytváření pohyblivých objektů ve hře)
        <ol>
          <li>CGameMode (pro výběr typu herního režimu, který chcete hrát, multiplayer atd.)
            <ol>
              <li>CPacman1 (pro počítání skóre nejlepších hráčů a jeho zobrazování)</li>
              <li>CPacman2 (jako druhý Pacman pro hraní více hráčů)</li>
            </ol>
          </li>
          <li>CSkill (pro různé typy schopností, které mohou mít duchové a další "nepřátelé")
            <ol>
              <li>CGhost1 (duchové, kteří budou pronásledovat Pacmana a jejich vzhled atd.)</li>
              <li>CGhost2 (duchové, kteří budou pronásledovat Pacmana a jejich vzhled atd.)</li>
              <li>CGhost3 (duchové, kteří budou pronásledovat Pacmana a jejich vzhled atd.)</li>
              <li>CGhost4 (duchové, kteří budou pronásledovat Pacmana a jejich vzhled atd.)</li>
            </ol>
          </li>
        </ol>
      </li>
</ol>

<h2>Popis pouziti polymorfismu ve hre</h2>
Polymofismus ve hre jsem se rozhodl pouzit ve tride Skill pro ruzne chovani vsech 4 duchu dle nastaveni ktere jim urci
hrac v souborech hry. <br>
CSkill muze byt abstraktni tridou s ciste virtualni funkci jako je followingStyle(). Tato funkce
by pak byla prepsana v kazde podtride, aby implementovala konkretni dovednost, kterou ma kazdy typ ducha jinou.

Ve tride CFruit pro ruzne nastaveni schopnosti co dane specialni ovoce prida hraci. <br>
Diky polymorfismu muzeme zpracovavat vsechny typy ovoce pomoci ukazatele nebo reference CFruit a pri volaní funkce
effectOnPacman() se provede prislusny efekt pro aktualni typ ovoce.<br>

Ve tride CGameMode pro ruzne chovani dvo pacmanu pro multiplayer.<br>
Opet by se dal polymorfismus pouzit pro ruzne chovani duchu napriklad se zavolanim funkce pacmanAppereance() by se se dalo
jednoduse nastavit jiny vzhled duchu pro kazdeho ducha v multiplayer jiny vzhled nez pro singleplayer aby je hraci mezi sebou rozeznali.<br>
