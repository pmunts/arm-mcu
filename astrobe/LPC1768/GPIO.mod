MODULE GPIO;

(* Bitband GPIO pin definitions for the LPC1768 Cortex-M3 microcontroller *)

(* Copyright (C)2015, Philip Munts, President, Munts AM Corp.                  *)
(*                                                                             *)
(* Redistribution and use in source and binary forms, with or without          *)
(* modification, are permitted provided that the following conditions are met: *)
(*                                                                             *)
(**  Redistributions of source code must retain the above copyright notice,    *)
(*   this list of conditions and the following disclaimer.                     *)
(*                                                                             *)
(* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" *)
(* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE   *)
(* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  *)
(* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE   *)
(* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR         *)
(* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF        *)
(* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS    *)
(* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN     *)
(* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)     *)
(* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE  *)
(* POSSIBILITY OF SUCH DAMAGE.                                                 *)

(* GPIO pins are numbered sequentially from the least significant bit of the   *)
(* lowest GPIO port to the highest port and bit.                               *)

(* Each GPIO pin has three constants defined for it: DirN, MaskN, and PinN.    *)
(* These map to the Cortex-M3 bitband addresses for that particular GPIO pin.  *)

CONST
  Dir0*    = 23380000H; (* P0.0  *)
  Mask0*   = 23380200H;
  Pin0*    = 23380280H;

  Dir1*    = 23380004H; (* P0.1  *)
  Mask1*   = 23380204H;
  Pin1*    = 23380284H;

  Dir2*    = 23380008H; (* P0.2  *)
  Mask2*   = 23380208H;
  Pin2*    = 23380288H;

  Dir3*    = 2338000CH; (* P0.3  *)
  Mask3*   = 2338020CH;
  Pin3*    = 2338028CH;

  Dir4*    = 23380010H; (* P0.4  *)
  Mask4*   = 23380210H;
  Pin4*    = 23380290H;

  Dir5*    = 23380014H; (* P0.5  *)
  Mask5*   = 23380214H;
  Pin5*    = 23380294H;

  Dir6*    = 23380018H; (* P0.6  *)
  Mask6*   = 23380218H;
  Pin6*    = 23380298H;

  Dir7*    = 2338001CH; (* P0.7  *)
  Mask7*   = 2338021CH;
  Pin7*    = 2338029CH;

  Dir8*    = 23380020H; (* P0.8  *)
  Mask8*   = 23380220H;
  Pin8*    = 233802A0H;

  Dir9*    = 23380024H; (* P0.9  *)
  Mask9*   = 23380224H;
  Pin9*    = 233802A4H;

  Dir10*   = 23380028H; (* P0.10 *)
  Mask10*  = 23380228H;
  Pin10*   = 233802A8H;

  Dir11*   = 2338002CH; (* P0.11 *)
  Mask11*  = 2338022CH;
  Pin11*   = 233802ACH;

  Dir12*   = 23380030H; (* P0.12 *)
  Mask12*  = 23380230H;
  Pin12*   = 233802B0H;

  Dir13*   = 23380034H; (* P0.13 *)
  Mask13*  = 23380234H;
  Pin13*   = 233802B4H;

  Dir14*   = 23380038H; (* P0.14 *)
  Mask14*  = 23380238H;
  Pin14*   = 233802B8H;

  Dir15*   = 2338003CH; (* P0.15 *)
  Mask15*  = 2338023CH;
  Pin15*   = 233802BCH;

  Dir16*   = 23380040H; (* P0.16 *)
  Mask16*  = 23380240H;
  Pin16*   = 233802C0H;

  Dir17*   = 23380044H; (* P0.17 *)
  Mask17*  = 23380244H;
  Pin17*   = 233802C4H;

  Dir18*   = 23380048H; (* P0.18 *)
  Mask18*  = 23380248H;
  Pin18*   = 233802C8H;

  Dir19*   = 2338004CH; (* P0.19 *)
  Mask19*  = 2338024CH;
  Pin19*   = 233802CCH;

  Dir20*   = 23380050H; (* P0.20 *)
  Mask20*  = 23380250H;
  Pin20*   = 233802D0H;

  Dir21*   = 23380054H; (* P0.21 *)
  Mask21*  = 23380254H;
  Pin21*   = 233802D4H;

  Dir22*   = 23380058H; (* P0.22 *)
  Mask22*  = 23380258H;
  Pin22*   = 233802D8H;

  Dir23*   = 2338005CH; (* P0.23 *)
  Mask23*  = 2338025CH;
  Pin23*   = 233802DCH;

  Dir24*   = 23380060H; (* P0.24 *)
  Mask24*  = 23380260H;
  Pin24*   = 233802E0H;

  Dir25*   = 23380064H; (* P0.25 *)
  Mask25*  = 23380264H;
  Pin25*   = 233802E4H;

  Dir26*   = 23380068H; (* P0.26 *)
  Mask26*  = 23380268H;
  Pin26*   = 233802E8H;

  Dir27*   = 2338006CH; (* P0.27 *)
  Mask27*  = 2338026CH;
  Pin27*   = 233802ECH;

  Dir28*   = 23380070H; (* P0.28 *)
  Mask28*  = 23380270H;
  Pin28*   = 233802F0H;

  Dir29*   = 23380074H; (* P0.29 *)
  Mask29*  = 23380274H;
  Pin29*   = 233802F4H;

  Dir30*   = 23380078H; (* P0.30 *)
  Mask30*  = 23380278H;
  Pin30*   = 233802F8H;

  Dir31*   = 2338007CH; (* P0.31 *)
  Mask31*  = 2338027CH;
  Pin31*   = 233802FCH;

  Dir32*   = 23380400H; (* P1.0  *)
  Mask32*  = 23380600H;
  Pin32*   = 23380680H;

  Dir33*   = 23380404H; (* P1.1  *)
  Mask33*  = 23380604H;
  Pin33*   = 23380684H;

  Dir34*   = 23380408H; (* P1.2  *)
  Mask34*  = 23380608H;
  Pin34*   = 23380688H;

  Dir35*   = 2338040CH; (* P1.3  *)
  Mask35*  = 2338060CH;
  Pin35*   = 2338068CH;

  Dir36*   = 23380410H; (* P1.4  *)
  Mask36*  = 23380610H;
  Pin36*   = 23380690H;

  Dir37*   = 23380414H; (* P1.5  *)
  Mask37*  = 23380614H;
  Pin37*   = 23380694H;

  Dir38*   = 23380418H; (* P1.6  *)
  Mask38*  = 23380618H;
  Pin38*   = 23380698H;

  Dir39*   = 2338041CH; (* P1.7  *)
  Mask39*  = 2338061CH;
  Pin39*   = 2338069CH;

  Dir40*   = 23380420H; (* P1.8  *)
  Mask40*  = 23380620H;
  Pin40*   = 233806A0H;

  Dir41*   = 23380424H; (* P1.9  *)
  Mask41*  = 23380624H;
  Pin41*   = 233806A4H;

  Dir42*   = 23380428H; (* P1.10 *)
  Mask42*  = 23380628H;
  Pin42*   = 233806A8H;

  Dir43*   = 2338042CH; (* P1.11 *)
  Mask43*  = 2338062CH;
  Pin43*   = 233806ACH;

  Dir44*   = 23380430H; (* P1.12 *)
  Mask44*  = 23380630H;
  Pin44*   = 233806B0H;

  Dir45*   = 23380434H; (* P1.13 *)
  Mask45*  = 23380634H;
  Pin45*   = 233806B4H;

  Dir46*   = 23380438H; (* P1.14 *)
  Mask46*  = 23380638H;
  Pin46*   = 233806B8H;

  Dir47*   = 2338043CH; (* P1.15 *)
  Mask47*  = 2338063CH;
  Pin47*   = 233806BCH;

  Dir48*   = 23380440H; (* P1.16 *)
  Mask48*  = 23380640H;
  Pin48*   = 233806C0H;

  Dir49*   = 23380444H; (* P1.17 *)
  Mask49*  = 23380644H;
  Pin49*   = 233806C4H;

  Dir50*   = 23380448H; (* P1.18 *)
  Mask50*  = 23380648H;
  Pin50*   = 233806C8H;

  Dir51*   = 2338044CH; (* P1.19 *)
  Mask51*  = 2338064CH;
  Pin51*   = 233806CCH;

  Dir52*   = 23380450H; (* P1.20 *)
  Mask52*  = 23380650H;
  Pin52*   = 233806D0H;

  Dir53*   = 23380454H; (* P1.21 *)
  Mask53*  = 23380654H;
  Pin53*   = 233806D4H;

  Dir54*   = 23380458H; (* P1.22 *)
  Mask54*  = 23380658H;
  Pin54*   = 233806D8H;

  Dir55*   = 2338045CH; (* P1.23 *)
  Mask55*  = 2338065CH;
  Pin55*   = 233806DCH;

  Dir56*   = 23380460H; (* P1.24 *)
  Mask56*  = 23380660H;
  Pin56*   = 233806E0H;

  Dir57*   = 23380464H; (* P1.25 *)
  Mask57*  = 23380664H;
  Pin57*   = 233806E4H;

  Dir58*   = 23380468H; (* P1.26 *)
  Mask58*  = 23380668H;
  Pin58*   = 233806E8H;

  Dir59*   = 2338046CH; (* P1.27 *)
  Mask59*  = 2338066CH;
  Pin59*   = 233806ECH;

  Dir60*   = 23380470H; (* P1.28 *)
  Mask60*  = 23380670H;
  Pin60*   = 233806F0H;

  Dir61*   = 23380474H; (* P1.29 *)
  Mask61*  = 23380674H;
  Pin61*   = 233806F4H;

  Dir62*   = 23380478H; (* P1.30 *)
  Mask62*  = 23380678H;
  Pin62*   = 233806F8H;

  Dir63*   = 2338047CH; (* P1.31 *)
  Mask63*  = 2338067CH;
  Pin63*   = 233806FCH;

  Dir64*   = 23380800H; (* P2.0  *)
  Mask64*  = 23380A00H;
  Pin64*   = 23380A80H;

  Dir65*   = 23380804H; (* P2.1  *)
  Mask65*  = 23380A04H;
  Pin65*   = 23380A84H;

  Dir66*   = 23380808H; (* P2.2  *)
  Mask66*  = 23380A08H;
  Pin66*   = 23380A88H;

  Dir67*   = 2338080CH; (* P2.3  *)
  Mask67*  = 23380A0CH;
  Pin67*   = 23380A8CH;

  Dir68*   = 23380810H; (* P2.4  *)
  Mask68*  = 23380A10H;
  Pin68*   = 23380A90H;

  Dir69*   = 23380814H; (* P2.5  *)
  Mask69*  = 23380A14H;
  Pin69*   = 23380A94H;

  Dir70*   = 23380818H; (* P2.6  *)
  Mask70*  = 23380A18H;
  Pin70*   = 23380A98H;

  Dir71*   = 2338081CH; (* P2.7  *)
  Mask71*  = 23380A1CH;
  Pin71*   = 23380A9CH;

  Dir72*   = 23380820H; (* P2.8  *)
  Mask72*  = 23380A20H;
  Pin72*   = 23380AA0H;

  Dir73*   = 23380824H; (* P2.9  *)
  Mask73*  = 23380A24H;
  Pin73*   = 23380AA4H;

  Dir74*   = 23380828H; (* P2.10 *)
  Mask74*  = 23380A28H;
  Pin74*   = 23380AA8H;

  Dir75*   = 2338082CH; (* P2.11 *)
  Mask75*  = 23380A2CH;
  Pin75*   = 23380AACH;

  Dir76*   = 23380830H; (* P2.12 *)
  Mask76*  = 23380A30H;
  Pin76*   = 23380AB0H;

  Dir77*   = 23380834H; (* P2.13 *)
  Mask77*  = 23380A34H;
  Pin77*   = 23380AB4H;

  Dir78*   = 23380838H; (* P2.14 *)
  Mask78*  = 23380A38H;
  Pin78*   = 23380AB8H;

  Dir79*   = 2338083CH; (* P2.15 *)
  Mask79*  = 23380A3CH;
  Pin79*   = 23380ABCH;

  Dir80*   = 23380840H; (* P2.16 *)
  Mask80*  = 23380A40H;
  Pin80*   = 23380AC0H;

  Dir81*   = 23380844H; (* P2.17 *)
  Mask81*  = 23380A44H;
  Pin81*   = 23380AC4H;

  Dir82*   = 23380848H; (* P2.18 *)
  Mask82*  = 23380A48H;
  Pin82*   = 23380AC8H;

  Dir83*   = 2338084CH; (* P2.19 *)
  Mask83*  = 23380A4CH;
  Pin83*   = 23380ACCH;

  Dir84*   = 23380850H; (* P2.20 *)
  Mask84*  = 23380A50H;
  Pin84*   = 23380AD0H;

  Dir85*   = 23380854H; (* P2.21 *)
  Mask85*  = 23380A54H;
  Pin85*   = 23380AD4H;

  Dir86*   = 23380858H; (* P2.22 *)
  Mask86*  = 23380A58H;
  Pin86*   = 23380AD8H;

  Dir87*   = 2338085CH; (* P2.23 *)
  Mask87*  = 23380A5CH;
  Pin87*   = 23380ADCH;

  Dir88*   = 23380860H; (* P2.24 *)
  Mask88*  = 23380A60H;
  Pin88*   = 23380AE0H;

  Dir89*   = 23380864H; (* P2.25 *)
  Mask89*  = 23380A64H;
  Pin89*   = 23380AE4H;

  Dir90*   = 23380868H; (* P2.26 *)
  Mask90*  = 23380A68H;
  Pin90*   = 23380AE8H;

  Dir91*   = 2338086CH; (* P2.27 *)
  Mask91*  = 23380A6CH;
  Pin91*   = 23380AECH;

  Dir92*   = 23380870H; (* P2.28 *)
  Mask92*  = 23380A70H;
  Pin92*   = 23380AF0H;

  Dir93*   = 23380874H; (* P2.29 *)
  Mask93*  = 23380A74H;
  Pin93*   = 23380AF4H;

  Dir94*   = 23380878H; (* P2.30 *)
  Mask94*  = 23380A78H;
  Pin94*   = 23380AF8H;

  Dir95*   = 2338087CH; (* P2.31 *)
  Mask95*  = 23380A7CH;
  Pin95*   = 23380AFCH;

  Dir96*   = 23380C00H; (* P3.0  *)
  Mask96*  = 23380E00H;
  Pin96*   = 23380E80H;

  Dir97*   = 23380C04H; (* P3.1  *)
  Mask97*  = 23380E04H;
  Pin97*   = 23380E84H;

  Dir98*   = 23380C08H; (* P3.2  *)
  Mask98*  = 23380E08H;
  Pin98*   = 23380E88H;

  Dir99*   = 23380C0CH; (* P3.3  *)
  Mask99*  = 23380E0CH;
  Pin99*   = 23380E8CH;

  Dir100*  = 23380C10H; (* P3.4  *)
  Mask100* = 23380E10H;
  Pin100*  = 23380E90H;

  Dir101*  = 23380C14H; (* P3.5  *)
  Mask101* = 23380E14H;
  Pin101*  = 23380E94H;

  Dir102*  = 23380C18H; (* P3.6  *)
  Mask102* = 23380E18H;
  Pin102*  = 23380E98H;

  Dir103*  = 23380C1CH; (* P3.7  *)
  Mask103* = 23380E1CH;
  Pin103*  = 23380E9CH;

  Dir104*  = 23380C20H; (* P3.8  *)
  Mask104* = 23380E20H;
  Pin104*  = 23380EA0H;

  Dir105*  = 23380C24H; (* P3.9  *)
  Mask105* = 23380E24H;
  Pin105*  = 23380EA4H;

  Dir106*  = 23380C28H; (* P3.10 *)
  Mask106* = 23380E28H;
  Pin106*  = 23380EA8H;

  Dir107*  = 23380C2CH; (* P3.11 *)
  Mask107* = 23380E2CH;
  Pin107*  = 23380EACH;

  Dir108*  = 23380C30H; (* P3.12 *)
  Mask108* = 23380E30H;
  Pin108*  = 23380EB0H;

  Dir109*  = 23380C34H; (* P3.13 *)
  Mask109* = 23380E34H;
  Pin109*  = 23380EB4H;

  Dir110*  = 23380C38H; (* P3.14 *)
  Mask110* = 23380E38H;
  Pin110*  = 23380EB8H;

  Dir111*  = 23380C3CH; (* P3.15 *)
  Mask111* = 23380E3CH;
  Pin111*  = 23380EBCH;

  Dir112*  = 23380C40H; (* P3.16 *)
  Mask112* = 23380E40H;
  Pin112*  = 23380EC0H;

  Dir113*  = 23380C44H; (* P3.17 *)
  Mask113* = 23380E44H;
  Pin113*  = 23380EC4H;

  Dir114*  = 23380C48H; (* P3.18 *)
  Mask114* = 23380E48H;
  Pin114*  = 23380EC8H;

  Dir115*  = 23380C4CH; (* P3.19 *)
  Mask115* = 23380E4CH;
  Pin115*  = 23380ECCH;

  Dir116*  = 23380C50H; (* P3.20 *)
  Mask116* = 23380E50H;
  Pin116*  = 23380ED0H;

  Dir117*  = 23380C54H; (* P3.21 *)
  Mask117* = 23380E54H;
  Pin117*  = 23380ED4H;

  Dir118*  = 23380C58H; (* P3.22 *)
  Mask118* = 23380E58H;
  Pin118*  = 23380ED8H;

  Dir119*  = 23380C5CH; (* P3.23 *)
  Mask119* = 23380E5CH;
  Pin119*  = 23380EDCH;

  Dir120*  = 23380C60H; (* P3.24 *)
  Mask120* = 23380E60H;
  Pin120*  = 23380EE0H;

  Dir121*  = 23380C64H; (* P3.25 *)
  Mask121* = 23380E64H;
  Pin121*  = 23380EE4H;

  Dir122*  = 23380C68H; (* P3.26 *)
  Mask122* = 23380E68H;
  Pin122*  = 23380EE8H;

  Dir123*  = 23380C6CH; (* P3.27 *)
  Mask123* = 23380E6CH;
  Pin123*  = 23380EECH;

  Dir124*  = 23380C70H; (* P3.28 *)
  Mask124* = 23380E70H;
  Pin124*  = 23380EF0H;

  Dir125*  = 23380C74H; (* P3.29 *)
  Mask125* = 23380E74H;
  Pin125*  = 23380EF4H;

  Dir126*  = 23380C78H; (* P3.30 *)
  Mask126* = 23380E78H;
  Pin126*  = 23380EF8H;

  Dir127*  = 23380C7CH; (* P3.31 *)
  Mask127* = 23380E7CH;
  Pin127*  = 23380EFCH;

  Dir128*  = 23381000H; (* P4.0  *)
  Mask128* = 23381200H;
  Pin128*  = 23381280H;

  Dir129*  = 23381004H; (* P4.1  *)
  Mask129* = 23381204H;
  Pin129*  = 23381284H;

  Dir130*  = 23381008H; (* P4.2  *)
  Mask130* = 23381208H;
  Pin130*  = 23381288H;

  Dir131*  = 2338100CH; (* P4.3  *)
  Mask131* = 2338120CH;
  Pin131*  = 2338128CH;

  Dir132*  = 23381010H; (* P4.4  *)
  Mask132* = 23381210H;
  Pin132*  = 23381290H;

  Dir133*  = 23381014H; (* P4.5  *)
  Mask133* = 23381214H;
  Pin133*  = 23381294H;

  Dir134*  = 23381018H; (* P4.6  *)
  Mask134* = 23381218H;
  Pin134*  = 23381298H;

  Dir135*  = 2338101CH; (* P4.7  *)
  Mask135* = 2338121CH;
  Pin135*  = 2338129CH;

  Dir136*  = 23381020H; (* P4.8  *)
  Mask136* = 23381220H;
  Pin136*  = 233812A0H;

  Dir137*  = 23381024H; (* P4.9  *)
  Mask137* = 23381224H;
  Pin137*  = 233812A4H;

  Dir138*  = 23381028H; (* P4.10 *)
  Mask138* = 23381228H;
  Pin138*  = 233812A8H;

  Dir139*  = 2338102CH; (* P4.11 *)
  Mask139* = 2338122CH;
  Pin139*  = 233812ACH;

  Dir140*  = 23381030H; (* P4.12 *)
  Mask140* = 23381230H;
  Pin140*  = 233812B0H;

  Dir141*  = 23381034H; (* P4.13 *)
  Mask141* = 23381234H;
  Pin141*  = 233812B4H;

  Dir142*  = 23381038H; (* P4.14 *)
  Mask142* = 23381238H;
  Pin142*  = 233812B8H;

  Dir143*  = 2338103CH; (* P4.15 *)
  Mask143* = 2338123CH;
  Pin143*  = 233812BCH;

  Dir144*  = 23381040H; (* P4.16 *)
  Mask144* = 23381240H;
  Pin144*  = 233812C0H;

  Dir145*  = 23381044H; (* P4.17 *)
  Mask145* = 23381244H;
  Pin145*  = 233812C4H;

  Dir146*  = 23381048H; (* P4.18 *)
  Mask146* = 23381248H;
  Pin146*  = 233812C8H;

  Dir147*  = 2338104CH; (* P4.19 *)
  Mask147* = 2338124CH;
  Pin147*  = 233812CCH;

  Dir148*  = 23381050H; (* P4.20 *)
  Mask148* = 23381250H;
  Pin148*  = 233812D0H;

  Dir149*  = 23381054H; (* P4.21 *)
  Mask149* = 23381254H;
  Pin149*  = 233812D4H;

  Dir150*  = 23381058H; (* P4.22 *)
  Mask150* = 23381258H;
  Pin150*  = 233812D8H;

  Dir151*  = 2338105CH; (* P4.23 *)
  Mask151* = 2338125CH;
  Pin151*  = 233812DCH;

  Dir152*  = 23381060H; (* P4.24 *)
  Mask152* = 23381260H;
  Pin152*  = 233812E0H;

  Dir153*  = 23381064H; (* P4.25 *)
  Mask153* = 23381264H;
  Pin153*  = 233812E4H;

  Dir154*  = 23381068H; (* P4.26 *)
  Mask154* = 23381268H;
  Pin154*  = 233812E8H;

  Dir155*  = 2338106CH; (* P4.27 *)
  Mask155* = 2338126CH;
  Pin155*  = 233812ECH;

  Dir156*  = 23381070H; (* P4.28 *)
  Mask156* = 23381270H;
  Pin156*  = 233812F0H;

  Dir157*  = 23381074H; (* P4.29 *)
  Mask157* = 23381274H;
  Pin157*  = 233812F4H;

  Dir158*  = 23381078H; (* P4.30 *)
  Mask158* = 23381278H;
  Pin158*  = 233812F8H;

  Dir159*  = 2338107CH; (* P4.31 *)
  Mask159* = 2338127CH;
  Pin159*  = 233812FCH;

(* Mask constants *)

  UNMASKED* = 0;
  MASKED*   = 1;

(* Data direction constants *)

  INPUT*    = 0;
  OUTPUT*   = 1;

(* Logic level constants *)

  HIGH*     = 1;
  LOW*      = 0;
  ON*       = 1;
  OFF*      = 0;

END GPIO.
