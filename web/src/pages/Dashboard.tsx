import LogoutForm from '@/components/LogoutForm';
import SendMessageForm from '@/components/MessageForm';

import {
  Card,
  CardHeader,
  CardTitle,
  CardDescription,
} from '@/components/ui/card';
import { useAuth } from '@/auth/AuthProvider';

const Dashboard = () => {
  const { user } = useAuth();
  return (
    <div className="flex flex-col items-center justify-between max-w-md space-y-4 mt-10 mx-10 sm:mx-auto">
      <Card className="w-full">
        <CardHeader>
          <CardTitle className="text-2xl">
            Hi, {user?.name === 'angelique' ? 'Angélique' : 'David'}
          </CardTitle>
          <CardDescription className="text-lg">
            Ready to send some love?
          </CardDescription>
        </CardHeader>
      </Card>
      <SendMessageForm />
      <LogoutForm />
    </div>
  );
};
export default Dashboard;
