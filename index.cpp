string zakatTernak(ternak &row){
    float nisab = cariNisabFloat(row.nama);
    if(row.jumlah>=nisab){
        row.wajibZakat=true;
        if(row.nama=="unta"){
            if(row.jumlah>=140){
                int jumlahEkor[2]; // usia 3 dan 2 tahun
                int sisaEkor[2]; // pembagi 50 dan 40
                string hasil;
                jumlahEkor[0]=row.jumlah / 50;
                sisaEkor[0]=row.jumlah%50;
                jumlahEkor[1]=row.jumlah/40;
                sisaEkor[1]=row.jumlah%40;
                int minSisa[3]; // jml50, jml40, sisa
                if(sisaEkor[0]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[0]);
                    return hasil +" ekor unta hiqqah (usia 3 tahun)";
                } else if(sisaEkor[1]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[1]);
                    return hasil +" ekor unta bintu labun (usia 2 tahun)";
                }  else {
                    minSisa[0] = jumlahEkor[0]; // hiqqah
                    minSisa[1] = 0;             // labun
                    minSisa[2] = sisaEkor[0];   // sisa
                                
                    int tempHiqqah = jumlahEkor[0];
                    int tempLabun  = 0;
                    int tempSisa   = sisaEkor[0];
                                
                    while(tempHiqqah >= 0) {
                        tempSisa = row.jumlah - (tempHiqqah * 50 + tempLabun * 40);
                        while(tempSisa>=40){
                            tempLabun++;
                            tempSisa-=40;
                        }
                        if(tempSisa < minSisa[2]) {
                            minSisa[0] = tempHiqqah;
                            minSisa[1] = tempLabun;
                            minSisa[2] = tempSisa;
                        }
                        if(tempSisa <= 0){

                            break;
                        }
                        tempHiqqah--;
                        tempLabun++;
                    }

                        hasil = "Wajib membayar " + to_string(minSisa[0]) + " ekor unta hiqqah (usia 3 tahun)";
                        if(minSisa[1] > 0)
                            hasil += " dan " + to_string(minSisa[1]) + " ekor unta bintu labun (usia 2 tahun)";
                        return hasil;
                    }     
                
            } else if(row.jumlah>120){
                return "3 ekor unta betina bintu labun (usia 2 tahun)";
            } else if(row.jumlah>90){
                return "2 ekor unta betina hiqqah (usia 3 tahun)";
            } else if(row.jumlah>75){
                return "2 ekor unta betina bintu labun (usia 2 tahun)";
            } else if(row.jumlah>60){
                return "1 ekor unta betina hiqqah (usia 4 tahun)";
            } else if(row.jumlah>45){
                return "1 ekor unta betina hiqqah (usia 3 tahun)";
            } else if(row.jumlah>35){
                return "1 ekor unta betina bintu labun (usia 2 tahun)";
            } else if(row.jumlah>24){
                return "1 ekor unta betina Bintu makhad (usia 1 tahun)";
            } else if(row.jumlah>19){
                return "4 ekor kambing umur 2 tahun, atau 4 ekor domba umur 1 tahun";
            } else if(row.jumlah>14){
                return "3 ekor kambing umur 2 tahun, atau 3 ekor domba umur 1 tahun";
            } else if(row.jumlah>9){
                return "2 ekor kambing umur 2 tahun, atau 2 ekor domba umur 1 tahun";
            } else {
                return "1 ekor kambing umur 2 tahun, atau 1 ekor domba umur 1 tahun";
            }
            
        } else if(row.nama=="sapi"){
            if(row.jumlah>=60){
                int jumlahEkor[2]; // usia 2 dan 1 tahun
                int sisaEkor[2]; // pembagi 40 dan 30
                string hasil;
                jumlahEkor[0]=row.jumlah / 40;
                sisaEkor[0]=row.jumlah%40;
                jumlahEkor[1]=row.jumlah/30;
                sisaEkor[1]=row.jumlah%30;
                int minSisa[3]; // jml50, jml40, sisa
                if(sisaEkor[0]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[0]);
                    return hasil +" ekor sapi musinnah (usia 2 tahun)";
                } else if(sisaEkor[1]==0){
                    hasil="Wajib membayar "+to_string(jumlahEkor[1]);
                    return hasil +" ekor sapi tabi' (usia 1 tahun)";
                }  else {
                    minSisa[0] = jumlahEkor[0]; // musinnah
                    minSisa[1] = 0;             // tabi'
                    minSisa[2] = sisaEkor[0];   // sisa
                                
                    int tempMusinnah = jumlahEkor[0];
                    int tempTabi  = 0;
                    int tempSisa   = sisaEkor[0];
                                
                    while(tempMusinnah >= 0) {
                        tempSisa = row.jumlah - (tempMusinnah * 40 + tempTabi * 30);
                        while(tempSisa>=30){
                            tempTabi++;
                            tempSisa-=30;
                        }
                        if(tempSisa < minSisa[2]) {
                            minSisa[0] = tempMusinnah;
                            minSisa[1] = tempTabi;
                            minSisa[2] = tempSisa;
                        }
                        if(tempSisa <= 0){

                            break;
                        }
                        tempMusinnah--;
                        tempTabi++;
                    }

                        hasil = "Wajib membayar " + to_string(minSisa[0]) + " ekor sapi musinnah (usia 2 tahun)";
                        if(minSisa[1] > 0)
                            hasil += " dan " + to_string(minSisa[1]) + " ekor sapi bintu tabi' (usia 1 tahun)";
                        return hasil;
                    }     
            } else if(row.jumlah>=40){
                return "1 ekor sapi musinnah (usia 2 tahun)";
            } else {
                return "1 ekor sapi tabi' (usia 1 tahun)";
            }

        } else if(row.nama=="kambing"){
            if(row.jumlah>=500){
                int hasil=row.jumlah/100;
                string strHasil ="Wajib membayar "+to_string(hasil);
                strHasil+=" ekor kambing usia 2 tahun atau domba usia 1 tahun";
                return strHasil;
            } else if(row.jumlah>=400){
                return "Wajib membayar 4 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            } else if(row.jumlah>200){
                return "Wajib membayar 3 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            } else if(row.jumlah>120){
                return "Wajib membayar 2 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            } else {
                return "Wajib membayar 1 ekor kambing usia 2 tahun atau domba usia 1 tahun";
            }
        } else {
            return "input tidak valid";
        }
    } else{
        row.wajibZakat=false;
        return "Tidak Wajib Membayar Zakat";
    }
};
