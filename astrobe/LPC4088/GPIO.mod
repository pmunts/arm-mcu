MODULE GPIO;

(* Bitband GPIO pin definitions for the LPC4088 Cortex-M4 microcontroller *)

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
(* These map to the Cortex-M4 bitband addresses for that particular GPIO pin.  *)

CONST
  Dir0*    = 23300000H; (* P0.0  *)
  Mask0*   = 23300200H;
  Pin0*    = 23300280H;

  Dir1*    = 23300004H; (* P0.1  *)
  Mask1*   = 23300204H;
  Pin1*    = 23300284H;

  Dir2*    = 23300008H; (* P0.2  *)
  Mask2*   = 23300208H;
  Pin2*    = 23300288H;

  Dir3*    = 2330000CH; (* P0.3  *)
  Mask3*   = 2330020CH;
  Pin3*    = 2330028CH;

  Dir4*    = 23300010H; (* P0.4  *)
  Mask4*   = 23300210H;
  Pin4*    = 23300290H;

  Dir5*    = 23300014H; (* P0.5  *)
  Mask5*   = 23300214H;
  Pin5*    = 23300294H;

  Dir6*    = 23300018H; (* P0.6  *)
  Mask6*   = 23300218H;
  Pin6*    = 23300298H;

  Dir7*    = 2330001CH; (* P0.7  *)
  Mask7*   = 2330021CH;
  Pin7*    = 2330029CH;

  Dir8*    = 23300020H; (* P0.8  *)
  Mask8*   = 23300220H;
  Pin8*    = 233002A0H;

  Dir9*    = 23300024H; (* P0.9  *)
  Mask9*   = 23300224H;
  Pin9*    = 233002A4H;

  Dir10*   = 23300028H; (* P0.10 *)
  Mask10*  = 23300228H;
  Pin10*   = 233002A8H;

  Dir11*   = 2330002CH; (* P0.11 *)
  Mask11*  = 2330022CH;
  Pin11*   = 233002ACH;

  Dir12*   = 23300030H; (* P0.12 *)
  Mask12*  = 23300230H;
  Pin12*   = 233002B0H;

  Dir13*   = 23300034H; (* P0.13 *)
  Mask13*  = 23300234H;
  Pin13*   = 233002B4H;

  Dir14*   = 23300038H; (* P0.14 *)
  Mask14*  = 23300238H;
  Pin14*   = 233002B8H;

  Dir15*   = 2330003CH; (* P0.15 *)
  Mask15*  = 2330023CH;
  Pin15*   = 233002BCH;

  Dir16*   = 23300040H; (* P0.16 *)
  Mask16*  = 23300240H;
  Pin16*   = 233002C0H;

  Dir17*   = 23300044H; (* P0.17 *)
  Mask17*  = 23300244H;
  Pin17*   = 233002C4H;

  Dir18*   = 23300048H; (* P0.18 *)
  Mask18*  = 23300248H;
  Pin18*   = 233002C8H;

  Dir19*   = 2330004CH; (* P0.19 *)
  Mask19*  = 2330024CH;
  Pin19*   = 233002CCH;

  Dir20*   = 23300050H; (* P0.20 *)
  Mask20*  = 23300250H;
  Pin20*   = 233002D0H;

  Dir21*   = 23300054H; (* P0.21 *)
  Mask21*  = 23300254H;
  Pin21*   = 233002D4H;

  Dir22*   = 23300058H; (* P0.22 *)
  Mask22*  = 23300258H;
  Pin22*   = 233002D8H;

  Dir23*   = 2330005CH; (* P0.23 *)
  Mask23*  = 2330025CH;
  Pin23*   = 233002DCH;

  Dir24*   = 23300060H; (* P0.24 *)
  Mask24*  = 23300260H;
  Pin24*   = 233002E0H;

  Dir25*   = 23300064H; (* P0.25 *)
  Mask25*  = 23300264H;
  Pin25*   = 233002E4H;

  Dir26*   = 23300068H; (* P0.26 *)
  Mask26*  = 23300268H;
  Pin26*   = 233002E8H;

  Dir27*   = 2330006CH; (* P0.27 *)
  Mask27*  = 2330026CH;
  Pin27*   = 233002ECH;

  Dir28*   = 23300070H; (* P0.28 *)
  Mask28*  = 23300270H;
  Pin28*   = 233002F0H;

  Dir29*   = 23300074H; (* P0.29 *)
  Mask29*  = 23300274H;
  Pin29*   = 233002F4H;

  Dir30*   = 23300078H; (* P0.30 *)
  Mask30*  = 23300278H;
  Pin30*   = 233002F8H;

  Dir31*   = 2330007CH; (* P0.31 *)
  Mask31*  = 2330027CH;
  Pin31*   = 233002FCH;

  Dir32*   = 23300400H; (* P1.0  *)
  Mask32*  = 23300600H;
  Pin32*   = 23300680H;

  Dir33*   = 23300404H; (* P1.1  *)
  Mask33*  = 23300604H;
  Pin33*   = 23300684H;

  Dir34*   = 23300408H; (* P1.2  *)
  Mask34*  = 23300608H;
  Pin34*   = 23300688H;

  Dir35*   = 2330040CH; (* P1.3  *)
  Mask35*  = 2330060CH;
  Pin35*   = 2330068CH;

  Dir36*   = 23300410H; (* P1.4  *)
  Mask36*  = 23300610H;
  Pin36*   = 23300690H;

  Dir37*   = 23300414H; (* P1.5  *)
  Mask37*  = 23300614H;
  Pin37*   = 23300694H;

  Dir38*   = 23300418H; (* P1.6  *)
  Mask38*  = 23300618H;
  Pin38*   = 23300698H;

  Dir39*   = 2330041CH; (* P1.7  *)
  Mask39*  = 2330061CH;
  Pin39*   = 2330069CH;

  Dir40*   = 23300420H; (* P1.8  *)
  Mask40*  = 23300620H;
  Pin40*   = 233006A0H;

  Dir41*   = 23300424H; (* P1.9  *)
  Mask41*  = 23300624H;
  Pin41*   = 233006A4H;

  Dir42*   = 23300428H; (* P1.10 *)
  Mask42*  = 23300628H;
  Pin42*   = 233006A8H;

  Dir43*   = 2330042CH; (* P1.11 *)
  Mask43*  = 2330062CH;
  Pin43*   = 233006ACH;

  Dir44*   = 23300430H; (* P1.12 *)
  Mask44*  = 23300630H;
  Pin44*   = 233006B0H;

  Dir45*   = 23300434H; (* P1.13 *)
  Mask45*  = 23300634H;
  Pin45*   = 233006B4H;

  Dir46*   = 23300438H; (* P1.14 *)
  Mask46*  = 23300638H;
  Pin46*   = 233006B8H;

  Dir47*   = 2330043CH; (* P1.15 *)
  Mask47*  = 2330063CH;
  Pin47*   = 233006BCH;

  Dir48*   = 23300440H; (* P1.16 *)
  Mask48*  = 23300640H;
  Pin48*   = 233006C0H;

  Dir49*   = 23300444H; (* P1.17 *)
  Mask49*  = 23300644H;
  Pin49*   = 233006C4H;

  Dir50*   = 23300448H; (* P1.18 *)
  Mask50*  = 23300648H;
  Pin50*   = 233006C8H;

  Dir51*   = 2330044CH; (* P1.19 *)
  Mask51*  = 2330064CH;
  Pin51*   = 233006CCH;

  Dir52*   = 23300450H; (* P1.20 *)
  Mask52*  = 23300650H;
  Pin52*   = 233006D0H;

  Dir53*   = 23300454H; (* P1.21 *)
  Mask53*  = 23300654H;
  Pin53*   = 233006D4H;

  Dir54*   = 23300458H; (* P1.22 *)
  Mask54*  = 23300658H;
  Pin54*   = 233006D8H;

  Dir55*   = 2330045CH; (* P1.23 *)
  Mask55*  = 2330065CH;
  Pin55*   = 233006DCH;

  Dir56*   = 23300460H; (* P1.24 *)
  Mask56*  = 23300660H;
  Pin56*   = 233006E0H;

  Dir57*   = 23300464H; (* P1.25 *)
  Mask57*  = 23300664H;
  Pin57*   = 233006E4H;

  Dir58*   = 23300468H; (* P1.26 *)
  Mask58*  = 23300668H;
  Pin58*   = 233006E8H;

  Dir59*   = 2330046CH; (* P1.27 *)
  Mask59*  = 2330066CH;
  Pin59*   = 233006ECH;

  Dir60*   = 23300470H; (* P1.28 *)
  Mask60*  = 23300670H;
  Pin60*   = 233006F0H;

  Dir61*   = 23300474H; (* P1.29 *)
  Mask61*  = 23300674H;
  Pin61*   = 233006F4H;

  Dir62*   = 23300478H; (* P1.30 *)
  Mask62*  = 23300678H;
  Pin62*   = 233006F8H;

  Dir63*   = 2330047CH; (* P1.31 *)
  Mask63*  = 2330067CH;
  Pin63*   = 233006FCH;

  Dir64*   = 23300800H; (* P2.0  *)
  Mask64*  = 23300A00H;
  Pin64*   = 23300A80H;

  Dir65*   = 23300804H; (* P2.1  *)
  Mask65*  = 23300A04H;
  Pin65*   = 23300A84H;

  Dir66*   = 23300808H; (* P2.2  *)
  Mask66*  = 23300A08H;
  Pin66*   = 23300A88H;

  Dir67*   = 2330080CH; (* P2.3  *)
  Mask67*  = 23300A0CH;
  Pin67*   = 23300A8CH;

  Dir68*   = 23300810H; (* P2.4  *)
  Mask68*  = 23300A10H;
  Pin68*   = 23300A90H;

  Dir69*   = 23300814H; (* P2.5  *)
  Mask69*  = 23300A14H;
  Pin69*   = 23300A94H;

  Dir70*   = 23300818H; (* P2.6  *)
  Mask70*  = 23300A18H;
  Pin70*   = 23300A98H;

  Dir71*   = 2330081CH; (* P2.7  *)
  Mask71*  = 23300A1CH;
  Pin71*   = 23300A9CH;

  Dir72*   = 23300820H; (* P2.8  *)
  Mask72*  = 23300A20H;
  Pin72*   = 23300AA0H;

  Dir73*   = 23300824H; (* P2.9  *)
  Mask73*  = 23300A24H;
  Pin73*   = 23300AA4H;

  Dir74*   = 23300828H; (* P2.10 *)
  Mask74*  = 23300A28H;
  Pin74*   = 23300AA8H;

  Dir75*   = 2330082CH; (* P2.11 *)
  Mask75*  = 23300A2CH;
  Pin75*   = 23300AACH;

  Dir76*   = 23300830H; (* P2.12 *)
  Mask76*  = 23300A30H;
  Pin76*   = 23300AB0H;

  Dir77*   = 23300834H; (* P2.13 *)
  Mask77*  = 23300A34H;
  Pin77*   = 23300AB4H;

  Dir78*   = 23300838H; (* P2.14 *)
  Mask78*  = 23300A38H;
  Pin78*   = 23300AB8H;

  Dir79*   = 2330083CH; (* P2.15 *)
  Mask79*  = 23300A3CH;
  Pin79*   = 23300ABCH;

  Dir80*   = 23300840H; (* P2.16 *)
  Mask80*  = 23300A40H;
  Pin80*   = 23300AC0H;

  Dir81*   = 23300844H; (* P2.17 *)
  Mask81*  = 23300A44H;
  Pin81*   = 23300AC4H;

  Dir82*   = 23300848H; (* P2.18 *)
  Mask82*  = 23300A48H;
  Pin82*   = 23300AC8H;

  Dir83*   = 2330084CH; (* P2.19 *)
  Mask83*  = 23300A4CH;
  Pin83*   = 23300ACCH;

  Dir84*   = 23300850H; (* P2.20 *)
  Mask84*  = 23300A50H;
  Pin84*   = 23300AD0H;

  Dir85*   = 23300854H; (* P2.21 *)
  Mask85*  = 23300A54H;
  Pin85*   = 23300AD4H;

  Dir86*   = 23300858H; (* P2.22 *)
  Mask86*  = 23300A58H;
  Pin86*   = 23300AD8H;

  Dir87*   = 2330085CH; (* P2.23 *)
  Mask87*  = 23300A5CH;
  Pin87*   = 23300ADCH;

  Dir88*   = 23300860H; (* P2.24 *)
  Mask88*  = 23300A60H;
  Pin88*   = 23300AE0H;

  Dir89*   = 23300864H; (* P2.25 *)
  Mask89*  = 23300A64H;
  Pin89*   = 23300AE4H;

  Dir90*   = 23300868H; (* P2.26 *)
  Mask90*  = 23300A68H;
  Pin90*   = 23300AE8H;

  Dir91*   = 2330086CH; (* P2.27 *)
  Mask91*  = 23300A6CH;
  Pin91*   = 23300AECH;

  Dir92*   = 23300870H; (* P2.28 *)
  Mask92*  = 23300A70H;
  Pin92*   = 23300AF0H;

  Dir93*   = 23300874H; (* P2.29 *)
  Mask93*  = 23300A74H;
  Pin93*   = 23300AF4H;

  Dir94*   = 23300878H; (* P2.30 *)
  Mask94*  = 23300A78H;
  Pin94*   = 23300AF8H;

  Dir95*   = 2330087CH; (* P2.31 *)
  Mask95*  = 23300A7CH;
  Pin95*   = 23300AFCH;

  Dir96*   = 23300C00H; (* P3.0  *)
  Mask96*  = 23300E00H;
  Pin96*   = 23300E80H;

  Dir97*   = 23300C04H; (* P3.1  *)
  Mask97*  = 23300E04H;
  Pin97*   = 23300E84H;

  Dir98*   = 23300C08H; (* P3.2  *)
  Mask98*  = 23300E08H;
  Pin98*   = 23300E88H;

  Dir99*   = 23300C0CH; (* P3.3  *)
  Mask99*  = 23300E0CH;
  Pin99*   = 23300E8CH;

  Dir100*  = 23300C10H; (* P3.4  *)
  Mask100* = 23300E10H;
  Pin100*  = 23300E90H;

  Dir101*  = 23300C14H; (* P3.5  *)
  Mask101* = 23300E14H;
  Pin101*  = 23300E94H;

  Dir102*  = 23300C18H; (* P3.6  *)
  Mask102* = 23300E18H;
  Pin102*  = 23300E98H;

  Dir103*  = 23300C1CH; (* P3.7  *)
  Mask103* = 23300E1CH;
  Pin103*  = 23300E9CH;

  Dir104*  = 23300C20H; (* P3.8  *)
  Mask104* = 23300E20H;
  Pin104*  = 23300EA0H;

  Dir105*  = 23300C24H; (* P3.9  *)
  Mask105* = 23300E24H;
  Pin105*  = 23300EA4H;

  Dir106*  = 23300C28H; (* P3.10 *)
  Mask106* = 23300E28H;
  Pin106*  = 23300EA8H;

  Dir107*  = 23300C2CH; (* P3.11 *)
  Mask107* = 23300E2CH;
  Pin107*  = 23300EACH;

  Dir108*  = 23300C30H; (* P3.12 *)
  Mask108* = 23300E30H;
  Pin108*  = 23300EB0H;

  Dir109*  = 23300C34H; (* P3.13 *)
  Mask109* = 23300E34H;
  Pin109*  = 23300EB4H;

  Dir110*  = 23300C38H; (* P3.14 *)
  Mask110* = 23300E38H;
  Pin110*  = 23300EB8H;

  Dir111*  = 23300C3CH; (* P3.15 *)
  Mask111* = 23300E3CH;
  Pin111*  = 23300EBCH;

  Dir112*  = 23300C40H; (* P3.16 *)
  Mask112* = 23300E40H;
  Pin112*  = 23300EC0H;

  Dir113*  = 23300C44H; (* P3.17 *)
  Mask113* = 23300E44H;
  Pin113*  = 23300EC4H;

  Dir114*  = 23300C48H; (* P3.18 *)
  Mask114* = 23300E48H;
  Pin114*  = 23300EC8H;

  Dir115*  = 23300C4CH; (* P3.19 *)
  Mask115* = 23300E4CH;
  Pin115*  = 23300ECCH;

  Dir116*  = 23300C50H; (* P3.20 *)
  Mask116* = 23300E50H;
  Pin116*  = 23300ED0H;

  Dir117*  = 23300C54H; (* P3.21 *)
  Mask117* = 23300E54H;
  Pin117*  = 23300ED4H;

  Dir118*  = 23300C58H; (* P3.22 *)
  Mask118* = 23300E58H;
  Pin118*  = 23300ED8H;

  Dir119*  = 23300C5CH; (* P3.23 *)
  Mask119* = 23300E5CH;
  Pin119*  = 23300EDCH;

  Dir120*  = 23300C60H; (* P3.24 *)
  Mask120* = 23300E60H;
  Pin120*  = 23300EE0H;

  Dir121*  = 23300C64H; (* P3.25 *)
  Mask121* = 23300E64H;
  Pin121*  = 23300EE4H;

  Dir122*  = 23300C68H; (* P3.26 *)
  Mask122* = 23300E68H;
  Pin122*  = 23300EE8H;

  Dir123*  = 23300C6CH; (* P3.27 *)
  Mask123* = 23300E6CH;
  Pin123*  = 23300EECH;

  Dir124*  = 23300C70H; (* P3.28 *)
  Mask124* = 23300E70H;
  Pin124*  = 23300EF0H;

  Dir125*  = 23300C74H; (* P3.29 *)
  Mask125* = 23300E74H;
  Pin125*  = 23300EF4H;

  Dir126*  = 23300C78H; (* P3.30 *)
  Mask126* = 23300E78H;
  Pin126*  = 23300EF8H;

  Dir127*  = 23300C7CH; (* P3.31 *)
  Mask127* = 23300E7CH;
  Pin127*  = 23300EFCH;

  Dir128*  = 23301000H; (* P4.0  *)
  Mask128* = 23301200H;
  Pin128*  = 23301280H;

  Dir129*  = 23301004H; (* P4.1  *)
  Mask129* = 23301204H;
  Pin129*  = 23301284H;

  Dir130*  = 23301008H; (* P4.2  *)
  Mask130* = 23301208H;
  Pin130*  = 23301288H;

  Dir131*  = 2330100CH; (* P4.3  *)
  Mask131* = 2330120CH;
  Pin131*  = 2330128CH;

  Dir132*  = 23301010H; (* P4.4  *)
  Mask132* = 23301210H;
  Pin132*  = 23301290H;

  Dir133*  = 23301014H; (* P4.5  *)
  Mask133* = 23301214H;
  Pin133*  = 23301294H;

  Dir134*  = 23301018H; (* P4.6  *)
  Mask134* = 23301218H;
  Pin134*  = 23301298H;

  Dir135*  = 2330101CH; (* P4.7  *)
  Mask135* = 2330121CH;
  Pin135*  = 2330129CH;

  Dir136*  = 23301020H; (* P4.8  *)
  Mask136* = 23301220H;
  Pin136*  = 233012A0H;

  Dir137*  = 23301024H; (* P4.9  *)
  Mask137* = 23301224H;
  Pin137*  = 233012A4H;

  Dir138*  = 23301028H; (* P4.10 *)
  Mask138* = 23301228H;
  Pin138*  = 233012A8H;

  Dir139*  = 2330102CH; (* P4.11 *)
  Mask139* = 2330122CH;
  Pin139*  = 233012ACH;

  Dir140*  = 23301030H; (* P4.12 *)
  Mask140* = 23301230H;
  Pin140*  = 233012B0H;

  Dir141*  = 23301034H; (* P4.13 *)
  Mask141* = 23301234H;
  Pin141*  = 233012B4H;

  Dir142*  = 23301038H; (* P4.14 *)
  Mask142* = 23301238H;
  Pin142*  = 233012B8H;

  Dir143*  = 2330103CH; (* P4.15 *)
  Mask143* = 2330123CH;
  Pin143*  = 233012BCH;

  Dir144*  = 23301040H; (* P4.16 *)
  Mask144* = 23301240H;
  Pin144*  = 233012C0H;

  Dir145*  = 23301044H; (* P4.17 *)
  Mask145* = 23301244H;
  Pin145*  = 233012C4H;

  Dir146*  = 23301048H; (* P4.18 *)
  Mask146* = 23301248H;
  Pin146*  = 233012C8H;

  Dir147*  = 2330104CH; (* P4.19 *)
  Mask147* = 2330124CH;
  Pin147*  = 233012CCH;

  Dir148*  = 23301050H; (* P4.20 *)
  Mask148* = 23301250H;
  Pin148*  = 233012D0H;

  Dir149*  = 23301054H; (* P4.21 *)
  Mask149* = 23301254H;
  Pin149*  = 233012D4H;

  Dir150*  = 23301058H; (* P4.22 *)
  Mask150* = 23301258H;
  Pin150*  = 233012D8H;

  Dir151*  = 2330105CH; (* P4.23 *)
  Mask151* = 2330125CH;
  Pin151*  = 233012DCH;

  Dir152*  = 23301060H; (* P4.24 *)
  Mask152* = 23301260H;
  Pin152*  = 233012E0H;

  Dir153*  = 23301064H; (* P4.25 *)
  Mask153* = 23301264H;
  Pin153*  = 233012E4H;

  Dir154*  = 23301068H; (* P4.26 *)
  Mask154* = 23301268H;
  Pin154*  = 233012E8H;

  Dir155*  = 2330106CH; (* P4.27 *)
  Mask155* = 2330126CH;
  Pin155*  = 233012ECH;

  Dir156*  = 23301070H; (* P4.28 *)
  Mask156* = 23301270H;
  Pin156*  = 233012F0H;

  Dir157*  = 23301074H; (* P4.29 *)
  Mask157* = 23301274H;
  Pin157*  = 233012F4H;

  Dir158*  = 23301078H; (* P4.30 *)
  Mask158* = 23301278H;
  Pin158*  = 233012F8H;

  Dir159*  = 2330107CH; (* P4.31 *)
  Mask159* = 2330127CH;
  Pin159*  = 233012FCH;

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
