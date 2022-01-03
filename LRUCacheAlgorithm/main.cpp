#include <stdio.h>
#include <stdlib.h>

typedef struct QNode
{
    struct QNode* prev;
    struct QNode* next;
    unsigned pageNumber;
} QNode;

typedef struct Queue
{
    unsigned count;             // ť�� ���� ��� ��
    unsigned numberOfFrames;    // ť�� ���� �� �ִ� �ִ� ��� ��
    QNode* front;
    QNode* rear;
} Queue;

typedef struct Hash
{
    int capacity;
    QNode** arr;    // �ؽ� ���̺�(�迭)
} Hash;

/// <summary>
/// ���ο� ��带 �����ϴ� �Լ�
/// </summary>
/// <param name="pageNumber">������ �ѹ�</param>
/// <returns></returns>
QNode* NewQNode(unsigned pageNumber)
{
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    if (temp)
    {
        // ���ο� ��带 �ʱ�ȭ
        temp->pageNumber = pageNumber;
        temp->prev = temp->next = NULL;
    }
    return temp;
}

/// <summary>
/// ����ִ� ť�� �����ϴ� �Լ�
/// </summary>
/// <param name="numberOfFrames">ť�� �ִ� ��� ��</param>
/// <returns>������ ť</returns>
Queue* CreateQueue(int numberOfFrames)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue)
    {
        // ���� ���� ť�� �ʱ�ȭ
        queue->front = queue->rear = nullptr;
        queue->count = 0;
        queue->numberOfFrames = numberOfFrames;
    }
    return queue;
}

/// <summary>
/// ����ִ� �ؽ� ���̺��� �����ϴ� �Լ�
/// �ؽ� ���̺�: Key�������� �� ���� ��ȸ�� �� �ִ� �ڷᱸ��
/// </summary>
/// <param name="capacity">�ؽ� ���̺�(�迭)�� �뷮</param>
/// <returns>������ �ؽ�</returns>
Hash* CreateHash(int capacity)
{
    Hash* hash = (Hash*)malloc(sizeof(hash));
    if (hash)
    {
        // ���� ���� �ؽø� �ʱ�ȭ
        hash->capacity = capacity;
        // capacity��ŭ�� QNode*�� �����ϴ� �迭 ����
        hash->arr = (QNode**)malloc(sizeof(QNode*) * hash->capacity);
        for (int i = 0; i < hash->capacity; i++)
            hash->arr[i] = nullptr;
    }
    return hash;
}

/// <summary>
/// ť�� �� ������ �ִ��� Ȯ���ϴ� �Լ�
/// </summary>
/// <param name="queue">��� ť</param>
/// <returns>�� ������ ������ true, �� �ܴ� false</returns>
bool AreAllFramesFull(Queue* queue)
{
    return queue->count = queue->numberOfFrames;
}

/// <summary>
/// ť�� ����ִ��� Ȯ���ϴ� �Լ�
/// </summary>
/// <param name="queue">��� ť</param>
/// <returns></returns>
bool IsQueueEmpty(Queue* queue)
{
    return queue->rear == nullptr;
}

// ť�� �������� �����ϴ� �Լ�
void DeQueue(Queue* queue)
{
    // ť�� ����ִ� ���
    if (IsQueueEmpty(queue)) return;
    // ť�� ��尡 �ϳ��� �ִ� ���(rear�� �������� ó��)
    if (queue->front == queue->rear) queue->front = nullptr;
    
    // ť�� rear(���� ��)
    QNode* temp = queue->rear;
    // ť�� rear�� �� ��带 ť�� rear�� �缳��
    queue->rear = queue->rear->prev;

    // ���Ӱ� ������ rear�� null�� �ƴ� ���(��尡 1���� ���� null�� ��)
    if (queue->rear)
    {
        // ���Ӱ� ������ rear�� next�� null�� ����
        queue->rear->next = nullptr;
    }

    // rear(���� ��)�� �޸� ����
    free(temp);
    // ť�� ���� ��� ���� �ϳ� ����
    queue->count--;
}

/// <summary>
/// ������(������ �ѹ�)�� ť�� �ؽÿ� �߰��ϴ� �Լ�
/// </summary>
/// <param name="queue">�ش� ť</param>
/// <param name="hash">�ش� �ؽ�</param>
/// <param name="pageNumber">������ �ѹ�</param>
void EnQueue(Queue* queue, Hash* hash, unsigned pageNumber)
{
    // ť�� �� ������ ���� ���
    // ť�� rear�� �ش��ϴ� �����͸� ť�� �ؽÿ��� ������
    if (AreAllFramesFull(queue))
    {
        hash->arr[queue->rear->pageNumber] = nullptr;
        DeQueue(queue);
    }

    // ť�� front�� ���ο� ��带 ����
    QNode* temp = NewQNode(pageNumber);
    temp->next = queue->front;

    // ť�� ����־��ٸ� �߰��� ��带 ť�� front�� rear�� ����
    if (IsQueueEmpty(queue))
    {
        queue->rear = temp;
        queue->front = temp;
    }
    // �� ���� ���� ť�� front�� temp�� ����
    else
    {
        queue->front->prev = temp;
        queue->front = temp;
    }

    // ť�� ���� ��� ���� +1��
    queue->count++;

    // �ؽÿ� ������ �ѹ��� �߰���
    hash->arr[pageNumber] = temp;
}

int main()
{
    // ť�� ����: �ֱٿ� ������ ��带 �׻� ����Ʈ�� ����
    Queue* q = CreateQueue(4);
    Hash* hash = CreateHash(10);

    system("pause");
    return 0;
}