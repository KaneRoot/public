INSERT INTO auteur VALUES ( 55, 'Abmayr W', 'Abmayr@cs.fhm.edu', 'http://www.informatik.fh-muenchen.de/~abmayr/abmayre.htm');
INSERT INTO auteur VALUES ( 20, 'Aho A', 'aho@cs.columbia.edu',  'http://www1.cs.columbia.edu/~aho/');
INSERT INTO auteur VALUES ( 21, 'Hopcroft J', 'jeh@cs.cornell.edu', 'http://www.cs.cornell.edu/jeh/');
INSERT INTO auteur VALUES ( 22, 'Ullman J', 'ullman@cs.stanford.edu', 'http://infolab.stanford.edu/~ullman/');
INSERT INTO auteur VALUES ( 23, 'Akl S', 'akl@cs.queensu.ca', 'http://www.cs.queensu.ca/~akl/');
INSERT INTO auteur VALUES ( 25, 'Adams R', null, null);
INSERT INTO auteur VALUES ( 26, 'Bischof L', 'Leanne.Bischof@csiro.au', 'http://www.cmis.csiro.au/leanne.bischof/ ');
INSERT INTO auteur VALUES ( 24, 'Toussaint G', 'godfried@cs.mcgill.ca', 'http://www-cgrl.cs.mcgill.ca/~godfried/');
INSERT INTO auteur VALUES ( 28, 'Powley W', 'wendy@cs.queensu.ca', 'http://www.cs.queensu.ca/home/wendy/');
INSERT INTO auteur VALUES ( 10, 'Amadasun M','amadasun@cs.stanford.edu', 'http://infolab.stanford.edu/~amadasun/');
INSERT INTO auteur VALUES ( 12, 'King R','king@cs.stanford.edu', 'http://infolab.stanford.edu/~king/');

INSERT INTO editeur VALUES (1, 'Teubner', '611 7878-285', '611 7878-420', 'Germany'); 
INSERT INTO editeur VALUES (2, 'Addison-Wesley', '415 402-2500', '415 402-2590', 'United States'); 
INSERT INTO editeur VALUES (3, 'elsevier', '20 7611 4500', '20 7611 4501', 'United Kingdom');
INSERT INTO editeur VALUES (4, 'asprs', '01 8038 6860', '01 8038 6861', 'United Kingdom');
INSERT INTO editeur VALUES (5, 'ieee-smc', '202 371-0101', '202 728-9614', 'United States'); 

INSERT INTO revue VALUES (11,'Computer Vision, Graphics, and Image Processing: Graphical Models and Image Processing', 5, 1989);
INSERT INTO revue VALUES (2,'Information Processing Letters', 2, 1979);
INSERT INTO revue VALUES (8,'Transactions on Pattern Analysis and Machine intelligence', 1, 1965);
INSERT INTO revue VALUES (31,'Pattern Recognition', 3, 1965);
INSERT INTO revue VALUES (9,'Photogrammetric Engineering and Remote Sensing', 4, 1988);
INSERT INTO revue VALUES (1,'Transactions on Systems, Man, and Cybernetics', NULL, 1962);
INSERT INTO revue VALUES (12,'Proc. of Geovision 99: International Symposium on Imaging Applications in Geology', 5, 1984);
INSERT INTO revue VALUES (35,'Physical Review', 2, 1985);
INSERT INTO revue VALUES (7,'Multimedia Tools and Applications, February 2000', 5, 1984);

INSERT INTO ouvrage VALUES (23, 'Einfuhrung in die digitale Bildverarbeitung', 1, 1994);
INSERT INTO ouvrage VALUES (15, 'Data structures and algorithms', 2, 1983);

INSERT INTO article VALUES (8, 35, 'Are randomly grown graphs really random', 121, 129, 64, 2); 
INSERT INTO article VALUES (11, 31, 'Some refinements of rough k-means clustering', 1481, 1491, 39, 8); 
INSERT INTO article VALUES (12, 8, 'Seeded region growing', 641, 647, 16, 6);
INSERT INTO article VALUES (41, 11, 'Radial decomposition of discs and spheres.', 325, 332, 55, 5);
INSERT INTO article VALUES (17, 2, 'Fast convex hull algorithm', 219, 222, 7, 5);
INSERT INTO article VALUES (19, 7, 'A Middleware for Broadband Networks.', 17, 19, 10, 2);
INSERT INTO article VALUES (25, 31, 'Low-level segmentation of multispectral images via agglomerative clustering of uniform neighbourhoods.', 216, 218, 21, 1);
INSERT INTO article VALUES (1,1,'Mental workload dynamics in adaptive interface design', 20,40,1,1);


INSERT INTO motcles VALUES (1, 'pattern recognition', null);
INSERT INTO motcles VALUES (2, 'segmentation', null);
INSERT INTO motcles VALUES (3, 'graph theory', null);
INSERT INTO motcles VALUES (4, 'image processing', null);
INSERT INTO motcles VALUES (5, 'hull', null);
INSERT INTO motcles VALUES (6, 'broadband Networks', null);

INSERT INTO organisme VALUES (1, 'Munich University of Applied Sciences Department of Computer Science', '+49 89 1265-1643', 'Germany');
INSERT INTO organisme VALUES (2, 'Computer Science Department Cornell University', '607 255-5396', 'United States');  
INSERT INTO organisme VALUES (3, 'Department of Computer Science Columbia University 513 Computer Science Building', '212 666-0140', 'United States');
INSERT INTO organisme VALUES (4, 'Computer Science Department, gates Computer Science Bldg. , Stanford University', '650 725-2588', 'United States'); 
INSERT INTO organisme VALUES (5, 'School of Computing, Queens University Kingston', '613 533-6513', 'Canada');
INSERT INTO organisme VALUES (6, 'School of Computer Science, University McConnell', '613 533-6000', 'Canada');
INSERT INTO organisme VALUES (7, 'Fakultï¿½t fï¿½r Informatik, Karlsruhe Universitï¿½ts', '49 21 608-3978', 'Germany');  
INSERT INTO organisme VALUES (8, 'CSIRO Mathematical and Information Sciences, Macquarie University Campus', '61 2 9325 3200', 'Australia');

INSERT INTO article_motcles VALUES (41, 1);
INSERT INTO article_motcles VALUES (41, 2);
INSERT INTO article_motcles VALUES (41, 4);
INSERT INTO article_motcles VALUES (17, 4);
INSERT INTO article_motcles VALUES (17, 5);
INSERT INTO article_motcles VALUES (19, 6);
INSERT INTO article_motcles VALUES (19, 3);
INSERT INTO article_motcles VALUES (25, 1);
INSERT INTO article_motcles VALUES (25, 2);
INSERT INTO article_motcles VALUES (25, 3);
INSERT INTO article_motcles VALUES (25, 4);
INSERT INTO article_motcles VALUES (11, 1);
INSERT INTO article_motcles VALUES (11, 4);

INSERT INTO ouvrage_auteur VALUES (23, 55);
INSERT INTO ouvrage_auteur VALUES (15, 20);
INSERT INTO ouvrage_auteur VALUES (15, 21);
INSERT INTO ouvrage_auteur VALUES (15, 22);

INSERT INTO article_auteur VALUES(12, 25);
INSERT INTO article_auteur VALUES(12, 26);
INSERT INTO article_auteur VALUES(8, 21);
INSERT INTO article_auteur VALUES(41, 25);
INSERT INTO article_auteur VALUES(17, 23);
INSERT INTO article_auteur VALUES(17, 24);
INSERT INTO article_auteur VALUES(19, 28);
INSERT INTO article_auteur VALUES(19, 23);
INSERT INTO article_auteur VALUES(25, 10);
INSERT INTO article_auteur VALUES(25, 12);
INSERT INTO article_auteur VALUES(11, 20);
INSERT INTO article_auteur VALUES(11, 21);
INSERT INTO article_auteur VALUES(11, 12);
INSERT INTO article_auteur VALUES(1,25);


INSERT INTO auteur_organisme VALUES (55, 1);
INSERT INTO auteur_organisme VALUES (20, 3);
INSERT INTO auteur_organisme VALUES (21, 2);
INSERT INTO auteur_organisme VALUES (22,4);
INSERT INTO auteur_organisme VALUES (23, 5);
INSERT INTO auteur_organisme VALUES (25, 7);
INSERT INTO auteur_organisme VALUES (26, 8);
INSERT INTO auteur_organisme VALUES (24, 5);
INSERT INTO auteur_organisme VALUES (24, 6);
INSERT INTO auteur_organisme VALUES (28, 5);
INSERT INTO auteur_organisme VALUES (10, 4);
INSERT INTO auteur_organisme VALUES (12, 4);
