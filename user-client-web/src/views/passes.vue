<template>
    <div>

    
    <div>
        <!-- пропуска -->
        
         <div v-if="res.passes!='no_passes'">
                <li v-for="pass in res.passes" v-bind:key="pass.passID" 
                
                style="list-style-type: none; padding: 0px;"
                v-on:click="changeSelect(pass.companyName);"
                :ref="setItemRef">
                <div class="passProgressBar" :style="{'width' : percentage + '%'}" 
                >

                    </div>
                    <div class="passTitle" > 
                        <div v-if="selected!=pass.companyName" >
                            {{pass.companyName}}    
                        </div>
                        
                        <div v-if="selected==pass.companyName" >
                            <div class="mainPassTitle">
                                {{pass.companyName}}
                            </div>
                        </div>
                    </div>
                    
                    <transition name="justSlide">
                    <div v-if="selected==pass.companyName"  class="pass">
                    <div class="passUsernameTitle">
                        Employee:
                    </div>
                    <div class="passUsername">
                        {{res.login}}
                    </div>
                        <div>
                        <qrcode-vue :value="pass.timecode" :size="300" level="H" />
                        </div>
                        <div style="padding: 10px; display:flex; justify-content: space-evenly;" class="passFooter">
                            <div>
                                {{pass.companyID}}
                            </div>
                            <div>
                                {{pass.passID}}
                            </div>
                        </div>
                    </div>
                    </transition>
                </li>
         </div>

    </div>
    <div v-if="res.passes==='no_passes'">
        <div class="noPasses">
        У вас пока нет пропусков!
        </div>
    </div>
    <div class="footer">
        Created by MonKeys
    </div>
    </div>
    
</template>


<script>

import QrcodeVue from 'qrcode.vue'

export default {
    name: 'passes',
    components : {
        QrcodeVue,
        
    },
    
    data() {
        return {
            itemRefs: [],
            percentage: 20,
            timeLeft: 0,
            selected: "none",
            auth :{
                login: '',
                password: '',
                loggedIn: false
            },
            res: {
                
            }
        }
    },
    
    methods: {
        updateDataFromStore() {
            console.log(this.$store.auth)
            this.data = this.$store.auth;
        },
        setItemRef(el) {
            if(el) {
                this.itemRefs.push(el)
            }
        },
        changeSelect(title){
            if(title==this.selected) {
                this.selected="none";
                
            }else
            {
                this.selected=title;
                setTimeout(function(){
                   var index = 0;
                
                    for(var i = 0; i < this.res.passes.length; i += 1) {
                        
                        if(this.res.passes[i].companyName === title) {
                            
                            index = i;
                        }
                    }
                    const el = this.itemRefs[index];
                    if(el){
                        
                        el.scrollIntoView({block: "start", behavior: "smooth"});
                    }
                    
                }.bind(this),2000);
                
            }
        },
        updateTempCodes: function(){
           
            if(this.$store.state.loggedin == true){
                const requestOptions = {
                    method: "POST",
                    headers: { "Content-Type": "application/json" },
                    body: JSON.stringify(
                        { 
                            "login": this.$store.state.auth.login, 
                            "password": this.$store.state.auth.password
                        }
                        )
                };
                
                fetch("http://192.168.31.234:8080/timecode", requestOptions)
                .then(response => 
                        response.json().then(data => ({
                            data: data,
                            status: response.status
                        })
                    ).then(res => {
                        this.res = res.data;
                    }));
                
            }
        },
        updateFloor(){
            var currentTime = Date.now();
            
            var floorStep = 30000;
            var floor = (currentTime % floorStep)/1000;
            this.percentage = (floor/30 *100);
            
            
        },
        scrollMeTo(refName) {
            var element = this.$refs[refName];
            var top = element.offsetTop;
            
            window.scrollTo(0, top);
        }

    },
    created() {
    setInterval(() => {
        this.updateFloor();
    }, 1);
    setInterval(() => {
        this.updateTempCodes();
    }, 1000);
    
  },
  computed: {
    percent() {
      return this.percentage.toFixed();
    },
    
    },
    beforeUpdate() {
    this.itemRefs = []
    },
    updated() {
    
    }
}
</script>


<style scoped>
.mainPassTitle{
    animation: mainTitle 1s;
    padding-right: 20%;
        font-size: 150%;
}

@keyframes mainTitle{
    0% {
        padding-right: 0%;
        font-size: 100%;
    }
    100% {
        padding-right: 20%;
        font-size: 150%;
    }
}
.footer{
    margin-top: 1000px;
}
.passTitle{
    color: black;
    font-family: "Minecraft";
    list-style-type: none;
    font-weight: 300;
    font-size: 300%;
    padding-bottom: 0%;
    text-align: end;
    z-index: 100;
    height: 100px;
}
.noPasses{
    font-family: "Minecraft";
    animation: rainbow 5s;
    font-size: 200%;
    animation-iteration-count: infinite;
}

@keyframes rainbow{
    0% {color: rgb(255, 196, 100);}
    10% {color: rgb(87, 255, 115);}
    20% {color: rgb(255, 157, 157);}
    30% {color: rgb(160, 241, 255);}
    40% {color: rgb(251, 114, 222);}
    50% {color: rgb(251, 79, 79);}
    60% {color: rgb(185, 63, 255);}
    70% {color: rgb(231, 72, 72);}
    80% {color: rgb(255, 0, 0);}
    90% {color: rgb(251, 255, 0);}
    100% {color: rgb(255, 196, 100);}
}
.passProgressBar{
    position: absolute;
    width: 375px;
    height: 100px;
    z-index: -100;
    animation: gradient 10s;
    animation-iteration-count: infinite;
}
.passFooter{
    font-family: "Minecraft";
    padding-bottom: 30%;
}
.passUsername{
    font-family: "Minecraft";
    color:black;
    padding-left: 10%;
    font-size: 200%;
    text-align: start;
    padding-bottom: 10%;
}

.passUsernameTitle{
    font-family: "Minecraft";
    color:black;

    font-size: 200%;
    text-align: start;
    
}

.passData{
    margin-bottom: 20%;
    animation: slideInside 2s;
    height: 600px;
}

.justSlide-enter-active{
    animation: slideInside 2s;
}

.justSlide-leave-active{
    animation: slideOut 2s;
}

@keyframes slideOut {
    0% {height: 600px;
    transform: translate(0, 0);}
    100% {height: 0px;
        transform: translate(-100%, 0);
        }
    
}

@keyframes slideInside {
    0% {height: 0px;
        transform: translate(100%, 0);
        }
    100% {height: 600px;
    transform: translate(0, 0);}
    
}

.pass{
    height:600px;
}

@keyframes gradient {
    0% {background-color: rgb(255, 196, 100);}
    10% {background-color: rgb(87, 255, 115);}
    20% {background-color: rgb(255, 157, 157);}
    30% {background-color: rgb(160, 241, 255);}
    40% {background-color: rgb(251, 114, 222);}
    50% {background-color: rgb(251, 79, 79);}
    60% {background-color: rgb(185, 63, 255);}
    70% {background-color: rgb(231, 72, 72);}
    80% {background-color: rgb(255, 0, 0);}
    90% {background-color: rgb(251, 255, 0);}
    100% {background-color: rgb(255, 122, 122);}

}


</style>