#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <ctime>
using namespace std;
//TODO:
//finish the mutex_lock
//build the Producer-Conumer model
//handle 1000 data???how to do it????
//build the clock to document the run time
const int RepositorySize = 100;
const int TheNumof_wanted = 1000;
const int Producer_Num = 64;
struct Repo{
	int buffer[RepositorySize];
	int load_position;
	int save_position;
	int produce_count;
	int consume_count;
	pthread_mutex_t mutex;
	pthread_mutex_t produce_count_mutex;
	pthread_mutex_t consume_count_mutex;
	pthread_cond_t notempty;//采用条件变量
	pthread_cond_t notfull;
}myRepo;
void Produce_Item(Repo* repost,int data){
	pthread_mutex_lock(&(repost->mutex));//注意传参方法
	while((repost->save_position + 1 )% RepositorySize == repost -> load_position){
		pthread_cond_wait(&(repost -> notfull), &(repost -> mutex));
		cout << "waiting" << endl;
	}
	repost -> buffer[repost -> save_position] = data;
	repost -> save_position ++;
	if(repost -> save_position >= RepositorySize){
		repost -> save_position = 0;
	}
	pthread_cond_signal(&(repost -> notempty));
	pthread_mutex_unlock(&(repost->mutex));
}
void Consume_Item(Repo* repost){
	pthread_mutex_lock(&(repost->mutex));
	while(repost -> save_position == repost -> load_position){
		pthread_cond_wait(&(repost -> notempty),&(repost->mutex));
	}
	int loaded = repost -> buffer[repost -> load_position];
	repost -> load_position ++;
	if(repost -> load_position >= RepositorySize){
		repost -> load_position = 0;
	}
	pthread_cond_signal(&(repost -> notfull));
	pthread_mutex_unlock(&(repost->mutex));
}
void *Producer_Task(void *arg){//void* A(void *arg)
	int InOrderTo_exit_without_lock = true;
	while(1){
		sleep(1);
		pthread_mutex_lock(&myRepo.produce_count_mutex);
		if(myRepo.produce_count < TheNumof_wanted){
			Produce_Item(&myRepo,2);
			myRepo.produce_count++;
			cout << "creating...." << endl;
		}
		else{//在这里直接退出会死锁！
			InOrderTo_exit_without_lock = false;
		}
		pthread_mutex_unlock(&myRepo.produce_count_mutex);
		if(InOrderTo_exit_without_lock == false){
			break;
		}
	}
	cout << "exiting Producer_Task" << endl;
}
void *Consume_Task(void *arg){
	int InOrderTo_exit_without_lock = true;
	while(1){
		sleep(1);
		pthread_mutex_lock(&myRepo.consume_count_mutex);
		if(myRepo.consume_count < TheNumof_wanted){
			Consume_Item(&myRepo);
			myRepo.consume_count ++;
			cout <<"consuming..." << endl;
		}
		else{
			InOrderTo_exit_without_lock = false;
		}
		pthread_mutex_unlock(&myRepo.consume_count_mutex);
		if(InOrderTo_exit_without_lock == false){
			break;//直接退出会死锁！
		}
	}
	cout << "exiting Consume_TASK" << endl;
}
void initialize_Repo(Repo* myRepo){
	myRepo -> load_position = 0;
	myRepo -> save_position = 0;
	myRepo -> produce_count = 0;
	myRepo -> consume_count = 0;
	int a = pthread_mutex_init(&(myRepo -> mutex),NULL);
	int b = pthread_mutex_init(&(myRepo -> produce_count_mutex),NULL);
	int c = pthread_mutex_init(&(myRepo -> produce_count_mutex),NULL);
	int d = pthread_cond_init(&(myRepo -> notempty),NULL);
	int e = pthread_cond_init(&(myRepo -> notfull),NULL);
}
int main(){
	initialize_Repo(&myRepo);
	pthread_t producer[Producer_Num];
	pthread_t consumer[Producer_Num];
	time_t start = time(NULL);
	for(int i = 0;i < Producer_Num;i ++){
		int a = pthread_create(&producer[i],NULL,&Producer_Task,NULL);
		int b = pthread_create(&consumer[i],NULL,&Consume_Task,NULL);
	}
	for(int i = 0;i < Producer_Num;i ++){
		pthread_join(producer[i],NULL);
	}

	for(int i = 0;i < Producer_Num;i ++){
		pthread_join(consumer[i],NULL);
	}
	time_t endtime = time(NULL); 
	cout <<  difftime(endtime,start) <<  " s\n"; 
	pthread_exit(NULL);
}